#include "ReadyQueue.hh"

ReadyQueue::ReadyQueue(IAlgorithm* algorithm)
    : alg(algorithm) {}

ReadyQueue::~ReadyQueue() {
    delete alg;
    alg = nullptr;
}

void ReadyQueue::enqueue(IProcess* process) {
    processes.push_back(process);
    // riordina la coda secondo l'algoritmo di scheduling
    sort(alg);
}

IProcess* ReadyQueue::dequeue() {
    if (processes.empty()) {
        return nullptr;
    }
    IProcess* p = processes.front();
    processes.pop_front();
    return p;
}

void ReadyQueue::sort(IAlgorithm* algorithm) {
    if (algorithm) {
        algorithm->sort(processes);
    }
}
