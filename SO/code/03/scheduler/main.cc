#include "Kernel.hh"
#include "Scheduler.hh"
#include "ReadyQueue.hh"
#include "Dispatcher.hh"
#include "CpuSimulator.hh"
// #include "AlgorithmFIFO.hh"
#include "AlgorithmSJF.hh"
#include "Process.hh"
#include <iostream>

int main() {

    // IQueue* queue = new ReadyQueue(new AlgorithmFIFO());
    IQueue* queue = new ReadyQueue(new AlgorithmSJF());
    IScheduler* scheduler = new Scheduler(queue);
    IDispatcher* dispatcher = new Dispatcher();
    IHWSimulator* cpu = new CpuSimulator();

    Kernel kernel(scheduler, queue, cpu, dispatcher);

    kernel.addProcess(new Process("A", 5));
    kernel.addProcess(new Process("B", 3));
    kernel.addProcess(new Process("C", 4));

    kernel.run(10);

    delete scheduler;
    delete queue;
    delete dispatcher;
    delete cpu;

    return 0;
}
