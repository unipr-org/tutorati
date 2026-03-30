#include "Dispatcher.hh"

void Dispatcher::dispatch(IQueue* queue, IHWSimulator* cpu) {
    if (cpu->isFree()) {
        IProcess* next = queue->dequeue();
        if (next != nullptr) {
            cpu->set(next);
        }
    }
}

void Dispatcher::dispatch(IQueue* queue, std::vector<IHWSimulator*>& cpus) {
    for (IHWSimulator* cpu : cpus) {
        dispatch(queue, cpu);
    }
}
