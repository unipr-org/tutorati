#ifndef PROCESS_HH
#define PROCESS_HH

#include <string>
#include "IProcess.hh"

class Process : public IProcess {
public:
    Process(std::string name, int burstTime, int priority = 0, int arrivalTime = 0);
    std::string getName() const override;
    int getRemainingTime() const override;
    int getTotalTime() const override;
    int getPriority() const override;
    int getArrivalTime() const override;

    void tick() override;

protected:
    void incrementPC() override;

private:
    std::string name;
    int totalTime;
    int remainingTime;
    int priority;
    int arrivalTime;
};

#endif // PROCESS_HH
