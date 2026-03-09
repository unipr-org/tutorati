#ifndef READY_QUEUE_HH
#define READY_QUEUE_HH

#include "IQueue.hh"
#include "IAlgorithm.hh"
#include <list>

class ReadyQueue : public IQueue {
public:
    ReadyQueue(IAlgorithm* algorithm);
    virtual ~ReadyQueue();

    void enqueue(IProcess* process) override;
    IProcess* dequeue() override;

protected:
    void sort(IAlgorithm* algorithm) override;

private:
    std::list<IProcess*> processes;
    IAlgorithm* alg;
};

#endif // READY_QUEUE_HH
