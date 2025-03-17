#ifndef IPROCESS_HH
#define IPROCESS_HH
#include <string>

class IProcess {
public:
    virtual ~IProcess() = default;
    virtual std::string getName() const = 0;
    virtual int getRemainingTime() const = 0;
    virtual int getTotalTime() const = 0;
    virtual void tick() = 0;

protected:
    virtual void incrementPC() = 0;
};

#endif // IPROCESS_HH