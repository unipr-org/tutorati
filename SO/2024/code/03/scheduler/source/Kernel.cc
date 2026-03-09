#include "Kernel.hh"

Kernel::Kernel(IScheduler* scheduler, IQueue* queue, IHWSimulator* cpu, IDispatcher* dispatcher)
    : scheduler(scheduler), queue(queue), cpu(cpu), dispatcher(dispatcher) {}

Kernel::~Kernel() {}

void Kernel::addProcess(IProcess* process) {
    scheduler->add(process);
}

void Kernel::run(int numTicks) {
    for (int tick = 0; tick < numTicks; ++tick) {
        // caricamento di un nuovo processo nella CPU se è libera
        dispatcher->dispatch(queue, cpu);
        // un (se un processo è in esecuzione)
        cpu->tick();
    }
}
