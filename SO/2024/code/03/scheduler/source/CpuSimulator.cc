#include "CpuSimulator.hh"

CpuSimulator::CpuSimulator() : currentProcess(nullptr) {}

void CpuSimulator::set(IProcess* process) {
    currentProcess = process;
}

IProcess* CpuSimulator::unset() {
    IProcess* temp = currentProcess;
    currentProcess = nullptr;
    return temp;
}

bool CpuSimulator::isFree() {
    return currentProcess == nullptr;
}

void CpuSimulator::tick() {
    if (currentProcess) {
        // tick sul processo corrente
        currentProcess->tick();

        // se il processo ha finito la sua esecuzione, libera la CPU
        if (currentProcess->getRemainingTime() == 0) {
            currentProcess = nullptr;
        }
    }
}
