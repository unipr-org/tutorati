#include "Kernel.hh"
#include "IPreemptive.hh"

Kernel::Kernel(IScheduler* scheduler, IQueue* queue, IHWSimulator* cpu, IDispatcher* dispatcher, IAlgorithm* algorithm)
    : scheduler(scheduler), queue(queue), cpus({cpu}), dispatcher(dispatcher), algorithm(algorithm),
      currentTick(0), completedCount(0), totalProcesses(0) {}

Kernel::Kernel(IScheduler* scheduler, IQueue* queue, std::vector<IHWSimulator*> cpus, IDispatcher* dispatcher, IAlgorithm* algorithm)
    : scheduler(scheduler), queue(queue), cpus(cpus), dispatcher(dispatcher), algorithm(algorithm),
      currentTick(0), completedCount(0), totalProcesses(0) {}

Kernel::~Kernel() {}

void Kernel::addProcess(IProcess* process) {
    scheduler->add(process);
}

void Kernel::run(int numTicks) {
    // verifica se l'algoritmo supporta la preemption
    IPreemptive* preemptive = dynamic_cast<IPreemptive*>(algorithm);

    for (int tick = 0; tick < numTicks; ++tick) {
        // 1. check preemption su tutti i core
        if (preemptive) {
            for (IHWSimulator* cpu : cpus) {
                if (!cpu->isFree() && preemptive->shouldPreempt(cpu)) {
                    IProcess* p = cpu->unset();
                    if (p != nullptr) {
                        queue->enqueue(p);
                    }
                }
            }
        }

        // 2. dispatch su tutti i core liberi
        dispatcher->dispatch(queue, cpus);

        // 3. tick su tutti i core
        for (IHWSimulator* cpu : cpus) {
            cpu->tick();
        }
    }
}

void Kernel::addPendingProcess(IProcess* process) {
    pendingProcesses.push_back(process);
    ProcessStats stats;
    stats.arrivalTime = process->getArrivalTime();
    stats.burstTime = process->getTotalTime();
    stats.startTime = -1;
    stats.completionTime = -1;
    processStats[process->getName()] = stats;
    totalProcesses++;
}

void Kernel::runUntilComplete() {
    IPreemptive* preemptive = dynamic_cast<IPreemptive*>(algorithm);
    currentTick = 0;
    completedCount = 0;

    while (completedCount < totalProcesses) {
        // 0. ADMIT — enqueue processi con arrivalTime <= currentTick
        for (int i = (int)pendingProcesses.size() - 1; i >= 0; --i) {
            if (pendingProcesses[i]->getArrivalTime() <= currentTick) {
                scheduler->add(pendingProcesses[i]);
                pendingProcesses.erase(pendingProcesses.begin() + i);
            }
        }

        // 1. PREEMPT
        if (preemptive) {
            for (IHWSimulator* cpu : cpus) {
                if (!cpu->isFree() && preemptive->shouldPreempt(cpu)) {
                    IProcess* p = cpu->unset();
                    if (p != nullptr) {
                        queue->enqueue(p);
                    }
                }
            }
        }

        // 2. DISPATCH
        dispatcher->dispatch(queue, cpus);

        // 3. RECORD START
        for (IHWSimulator* cpu : cpus) {
            if (!cpu->isFree()) {
                std::string name = cpu->getCurrentProcess()->getName();
                if (processStats[name].startTime == -1) {
                    processStats[name].startTime = currentTick;
                }
            }
        }

        // 4. GANTT LOG
        GanttRow row;
        row.tick = currentTick;
        for (IHWSimulator* cpu : cpus) {
            if (!cpu->isFree()) {
                row.cpuAssignments.push_back(cpu->getCurrentProcess()->getName());
            } else {
                row.cpuAssignments.push_back("-");
            }
        }
        ganttLog.push_back(row);

        // 5. TICK
        for (IHWSimulator* cpu : cpus) {
            IProcess* before = cpu->getCurrentProcess();
            cpu->tick();
            if (before != nullptr && cpu->isFree()) {
                // processo completato
                processStats[before->getName()].completionTime = currentTick + 1;
                completedCount++;
            }
        }

        // 6. currentTick++
        currentTick++;
    }
}

const std::map<std::string, ProcessStats>& Kernel::getStats() const {
    return processStats;
}

const std::vector<GanttRow>& Kernel::getGanttLog() const {
    return ganttLog;
}

int Kernel::getTotalTicks() const {
    return currentTick;
}
