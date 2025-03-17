#ifndef SCHEDULER_HH
#define SCHEDULER_HH

#include "IScheduler.hh"
#include "IQueue.hh"
#include "IProcess.hh"

class Scheduler : public IScheduler {
public:
    Scheduler(IQueue* q);
    void add(IProcess* process) override;
private:
    IQueue* queue;
};

#endif // SCHEDULER_HH
