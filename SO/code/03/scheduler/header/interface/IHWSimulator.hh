#ifndef IHWSIMULATOR_HH
#define IHWSIMULATOR_HH

class IProcess;

class IHWSimulator {
public:
    virtual ~IHWSimulator() = default;
    virtual void set(IProcess* process) = 0;
    virtual IProcess* unset() = 0;
    virtual bool isFree() = 0;
    virtual void tick() = 0;
};

#endif // IHWSIMULATOR_HH