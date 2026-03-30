#ifndef MULTILEVEL_QUEUE_HH
#define MULTILEVEL_QUEUE_HH

#include "IQueue.hh"
#include "IProcess.hh"
#include <map>

class MultilevelQueue : public IQueue {
public:
    MultilevelQueue();
    virtual ~MultilevelQueue();

    void addQueue(int priority, IQueue* queue);
    void enqueue(IProcess* process) override;
    IProcess* dequeue() override;

protected:
    void sort(IAlgorithm* algorithm) override;

private:
    std::map<int, IQueue*> queues;
};

#endif // MULTILEVEL_QUEUE_HH
