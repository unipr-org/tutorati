#ifndef KERNEL_HH
#define KERNEL_HH

#include "IScheduler.hh"
#include "IQueue.hh"
#include "IHWSimulator.hh"
#include "IDispatcher.hh"
#include "IProcess.hh"
#include "IAlgorithm.hh"
#include <vector>
#include <map>
#include <string>

struct ProcessStats {
    int arrivalTime;
    int burstTime;
    int startTime;       // -1 = non ancora avviato
    int completionTime;  // -1 = non ancora completato
};

struct GanttRow {
    int tick;
    std::vector<std::string> cpuAssignments; // nome processo o "-"
};

class Kernel {
public:
    // costruttore single-core (retrocompatibile)
    Kernel(IScheduler* scheduler, IQueue* queue, IHWSimulator* cpu, IDispatcher* dispatcher, IAlgorithm* algorithm = nullptr);
    // costruttore multi-core
    Kernel(IScheduler* scheduler, IQueue* queue, std::vector<IHWSimulator*> cpus, IDispatcher* dispatcher, IAlgorithm* algorithm = nullptr);
    ~Kernel();

    void addProcess(IProcess* process);
    void run(int numTicks);

    void addPendingProcess(IProcess* process);
    void runUntilComplete();
    const std::map<std::string, ProcessStats>& getStats() const;
    const std::vector<GanttRow>& getGanttLog() const;
    int getTotalTicks() const;

private:
    IScheduler* scheduler;
    IQueue* queue;
    std::vector<IHWSimulator*> cpus;
    IDispatcher* dispatcher;
    IAlgorithm* algorithm;

    std::vector<IProcess*> pendingProcesses;
    std::map<std::string, ProcessStats> processStats;
    std::vector<GanttRow> ganttLog;
    int currentTick;
    int completedCount;
    int totalProcesses;
};

#endif // KERNEL_HH
