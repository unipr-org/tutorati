#ifndef IPREEMPTIVE_HH
#define IPREEMPTIVE_HH

class IHWSimulator;

class IPreemptive {
public:
    virtual ~IPreemptive() = default;
    virtual bool shouldPreempt(IHWSimulator* cpu) const = 0;
};

#endif // IPREEMPTIVE_HH
