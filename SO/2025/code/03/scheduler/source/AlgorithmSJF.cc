#include "AlgorithmSJF.hh"

void AlgorithmSJF::sort(std::list<IProcess*>& processes) {

    // confronto dei processi in base al tempo rimanente
    processes.sort([](IProcess* a, IProcess* b) {
        if (a && b) {
            return a->getRemainingTime() < b->getRemainingTime();
        }
        return false;
        });
}
