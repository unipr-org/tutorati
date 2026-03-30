#ifndef CPU_SIMULATOR_HH
#define CPU_SIMULATOR_HH

#include "IHWSimulator.hh"
#include "IProcess.hh"

class CpuSimulator : public IHWSimulator {
public:
    CpuSimulator();
    void set(IProcess* process) override;
    IProcess* unset() override;
    bool isFree() override;
    void tick() override;
    int getRunningTicks() const override;
    IProcess* getCurrentProcess() const override;

private:
    IProcess* currentProcess;
    int runningTicks;
};

#endif // CPU_SIMULATOR_HH
