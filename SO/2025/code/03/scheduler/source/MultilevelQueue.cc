#include "MultilevelQueue.hh"

MultilevelQueue::MultilevelQueue() {}

MultilevelQueue::~MultilevelQueue() {}

void MultilevelQueue::addQueue(int priority, IQueue* queue) {
    queues[priority] = queue;
}

void MultilevelQueue::enqueue(IProcess* process) {
    int prio = process->getPriority();
    auto it = queues.find(prio);
    if (it != queues.end()) {
        it->second->enqueue(process);
    }
}

IProcess* MultilevelQueue::dequeue() {
    // itera dalla priorità più alta (0) alla più bassa
    for (auto& pair : queues) {
        IProcess* p = pair.second->dequeue();
        if (p != nullptr) {
            return p;
        }
    }
    return nullptr;
}

void MultilevelQueue::sort(IAlgorithm* algorithm) {
    // no-op: ogni sotto-coda ha il suo algoritmo
    (void)algorithm;
}
