#include "AlgorithmRR.hh"

AlgorithmRR::AlgorithmRR(int quantum) : quantum(quantum) {}

void AlgorithmRR::sort(std::list<IProcess*>& processes) {
    // FIFO: nessun riordinamento
    (void)processes;
}

bool AlgorithmRR::shouldPreempt(IHWSimulator* cpu) const {
    return cpu->getRunningTicks() >= quantum;
}
