#ifndef KERNEL_HH
#define KERNEL_HH

#include "IScheduler.hh"
#include "IQueue.hh"
#include "IHWSimulator.hh"
#include "IDispatcher.hh"
#include "IProcess.hh"

class Kernel {
public:
    // riceve le componenti già istanziate
    Kernel(IScheduler* scheduler, IQueue* queue, IHWSimulator* cpu, IDispatcher* dispatcher);
    ~Kernel();

    // aggiunge un processo al sistema tramite lo scheduler
    void addProcess(IProcess* process);

    // esegue la simulazione per un numero definito di tick
    void run(int numTicks);

private:
    IScheduler* scheduler;
    IQueue* queue;
    IHWSimulator* cpu;
    IDispatcher* dispatcher;
};

#endif // KERNEL_HH
