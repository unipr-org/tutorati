#include "Kernel.hh"
#include "Scheduler.hh"
#include "ReadyQueue.hh"
#include "Dispatcher.hh"
#include "CpuSimulator.hh"
#include "AlgorithmFIFO.hh"
#include "AlgorithmSJF.hh"
#include "AlgorithmRR.hh"
#include "MultilevelQueue.hh"
#include "Process.hh"
#include "ScenarioLoader.hh"
#include <iostream>
#include <string>

void demoFIFO() {
    std::cout << "=== Demo FIFO ===" << std::endl;

    IAlgorithm* alg = new AlgorithmFIFO();
    IQueue* queue = new ReadyQueue(alg);
    IScheduler* scheduler = new Scheduler(queue);
    IDispatcher* dispatcher = new Dispatcher();
    IHWSimulator* cpu = new CpuSimulator();

    Kernel kernel(scheduler, queue, cpu, dispatcher);

    kernel.addProcess(new Process("A", 5));
    kernel.addProcess(new Process("B", 3));
    kernel.addProcess(new Process("C", 4));

    kernel.run(12);

    delete scheduler;
    delete queue;
    delete dispatcher;
    delete cpu;
    delete alg;

    std::cout << std::endl;
}

void demoSJF() {
    std::cout << "=== Demo SJF ===" << std::endl;

    IAlgorithm* alg = new AlgorithmSJF();
    IQueue* queue = new ReadyQueue(alg);
    IScheduler* scheduler = new Scheduler(queue);
    IDispatcher* dispatcher = new Dispatcher();
    IHWSimulator* cpu = new CpuSimulator();

    Kernel kernel(scheduler, queue, cpu, dispatcher);

    kernel.addProcess(new Process("A", 5));
    kernel.addProcess(new Process("B", 3));
    kernel.addProcess(new Process("C", 4));

    kernel.run(12);

    delete scheduler;
    delete queue;
    delete dispatcher;
    delete cpu;
    delete alg;

    std::cout << std::endl;
}

void demoRR() {
    std::cout << "=== Demo Round Robin (quantum=2) ===" << std::endl;

    AlgorithmRR* alg = new AlgorithmRR(2);
    IQueue* queue = new ReadyQueue(alg);
    IScheduler* scheduler = new Scheduler(queue);
    IDispatcher* dispatcher = new Dispatcher();
    IHWSimulator* cpu = new CpuSimulator();

    Kernel kernel(scheduler, queue, cpu, dispatcher, alg);

    kernel.addProcess(new Process("A", 5));
    kernel.addProcess(new Process("B", 3));
    kernel.addProcess(new Process("C", 4));

    kernel.run(12);

    delete scheduler;
    delete queue;
    delete dispatcher;
    delete cpu;
    delete alg;

    std::cout << std::endl;
}

void demoMLQ() {
    std::cout << "=== Demo Multilevel Queue ===" << std::endl;

    // coda alta priorità con Round Robin (quantum=2)
    AlgorithmRR* algHigh = new AlgorithmRR(2);
    IQueue* highQueue = new ReadyQueue(algHigh);

    // coda bassa priorità con FIFO
    IAlgorithm* algLow = new AlgorithmFIFO();
    IQueue* lowQueue = new ReadyQueue(algLow);

    // multilevel queue
    MultilevelQueue* mlq = new MultilevelQueue();
    mlq->addQueue(0, highQueue);  // priorità 0 = alta
    mlq->addQueue(1, lowQueue);   // priorità 1 = bassa

    IScheduler* scheduler = new Scheduler(mlq);
    IDispatcher* dispatcher = new Dispatcher();
    IHWSimulator* cpu = new CpuSimulator();

    // l'algoritmo di preemption è quello della coda ad alta priorità
    Kernel kernel(scheduler, mlq, cpu, dispatcher, algHigh);

    // processi ad alta priorità (priority=0)
    kernel.addProcess(new Process("H1", 3, 0));
    kernel.addProcess(new Process("H2", 2, 0));

    // processi a bassa priorità (priority=1)
    kernel.addProcess(new Process("L1", 4, 1));
    kernel.addProcess(new Process("L2", 3, 1));

    kernel.run(15);

    delete scheduler;
    delete mlq;
    delete highQueue;
    delete lowQueue;
    delete dispatcher;
    delete cpu;
    delete algHigh;
    delete algLow;

    std::cout << std::endl;
}

void demoMultiCore() {
    std::cout << "=== Demo Multi-Core (2 CPU) ===" << std::endl;

    IAlgorithm* alg = new AlgorithmSJF();
    IQueue* queue = new ReadyQueue(alg);
    IScheduler* scheduler = new Scheduler(queue);
    IDispatcher* dispatcher = new Dispatcher();

    std::vector<IHWSimulator*> cpus;
    cpus.push_back(new CpuSimulator());
    cpus.push_back(new CpuSimulator());

    Kernel kernel(scheduler, queue, cpus, dispatcher);

    kernel.addProcess(new Process("A", 5));
    kernel.addProcess(new Process("B", 3));
    kernel.addProcess(new Process("C", 4));
    kernel.addProcess(new Process("D", 2));

    kernel.run(8);

    delete scheduler;
    delete queue;
    delete dispatcher;
    for (IHWSimulator* cpu : cpus) {
        delete cpu;
    }
    delete alg;

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // esegue tutte le demo
        demoFIFO();
        demoSJF();
        demoRR();
        demoMLQ();
        demoMultiCore();
    } else {
        std::string mode = argv[1];
        if (mode == "fifo") {
            demoFIFO();
        } else if (mode == "sjf") {
            demoSJF();
        } else if (mode == "rr") {
            demoRR();
        } else if (mode == "mlq") {
            demoMLQ();
        } else if (mode == "multicore") {
            demoMultiCore();
        } else if (mode == "--scenario" && argc >= 3) {
            std::string scenarioPath = argv[2];
            ScenarioLoader loader(scenarioPath);
            if (!loader.load()) { return 1; }
            loader.run();
            loader.writeResults();
        } else {
            std::cerr << "Uso: ./scheduler [fifo|sjf|rr|mlq|multicore|--scenario <path>]" << std::endl;
            return 1;
        }
    }

    return 0;
}
