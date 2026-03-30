#include "CpuSimulator.hh"

CpuSimulator::CpuSimulator() : currentProcess(nullptr), runningTicks(0) {}

void CpuSimulator::set(IProcess* process) {
    currentProcess = process;
    runningTicks = 0;
}

IProcess* CpuSimulator::unset() {
    IProcess* temp = currentProcess;
    currentProcess = nullptr;
    runningTicks = 0;
    return temp;
}

bool CpuSimulator::isFree() {
    return currentProcess == nullptr;
}

void CpuSimulator::tick() {
    if (currentProcess) {
        currentProcess->tick();
        runningTicks++;

        if (currentProcess->getRemainingTime() == 0) {
            currentProcess = nullptr;
            runningTicks = 0;
        }
    }
}

int CpuSimulator::getRunningTicks() const {
    return runningTicks;
}

IProcess* CpuSimulator::getCurrentProcess() const {
    return currentProcess;
}
