#include "Scheduler.hh"

Scheduler::Scheduler(IQueue* q) : queue(q) {}

void Scheduler::add(IProcess* process) {
    queue->enqueue(process);
}
