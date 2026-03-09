#ifndef ISCHEDULER_HH
#define ISCHEDULER_HH

class IProcess;

class IScheduler {
public:
    virtual ~IScheduler() = default;
    virtual void add(IProcess* process) = 0;
};

#endif // ISCHEDULER_HH