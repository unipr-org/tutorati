#include "Process.hh"

#ifdef DEBUG
#include <iostream>
#endif

Process::Process(std::string name, int burstTime, int priority, int arrivalTime)
    : name(name), totalTime(burstTime), remainingTime(burstTime), priority(priority), arrivalTime(arrivalTime) {}

std::string Process::getName() const {
    return name;
}

int Process::getRemainingTime() const {
    return remainingTime;
}

int Process::getTotalTime() const {
    return totalTime;
}

int Process::getPriority() const {
    return priority;
}

int Process::getArrivalTime() const {
    return arrivalTime;
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
