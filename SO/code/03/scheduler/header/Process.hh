#ifndef PROCESS_HH
#define PROCESS_HH

#include <string>
#include "IProcess.hh"

class Process : public IProcess {
public:
    Process(std::string name, int burstTime);
    std::string getName() const;
    int getRemainingTime() const;
    int getTotalTime() const;

    void tick() override;

protected:
    void incrementPC() override;

private:
    std::string name;
    int totalTime;
    int remainingTime;
};

#endif // PROCESS_HH
