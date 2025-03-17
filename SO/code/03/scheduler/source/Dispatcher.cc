#include "Dispatcher.hh"

void Dispatcher::dispatch(IQueue* queue, IHWSimulator* cpu) {
    if (cpu->isFree()) {  // verifica che la CPU sia libera
        IProcess* next = queue->dequeue();
        if (next != nullptr) {
            cpu->set(next);
        }
    }
}
