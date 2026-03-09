#include "Process.hh"

#ifdef DEBUG
#include <iostream>
#endif

Process::Process(std::string name, int burstTime)
    : name(name), totalTime(burstTime), remainingTime(burstTime) {}

std::string Process::getName() const {
    return name;
}

int Process::getRemainingTime() const {
    return remainingTime;
}

int Process::getTotalTime() const {
    return totalTime;
}

void Process::tick() {
#ifdef DEBUG
    std::cout << "Il processo " << name << " ha effettuato un tick\nTempo rimanente: " << remainingTime << std::endl;
#endif
    if (remainingTime > 0) {
        incrementPC();
    }
}

void Process::incrementPC() {
    if (remainingTime > 0) {
        remainingTime--;
    }
}
