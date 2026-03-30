#ifndef IQUEUE_HH
#define IQUEUE_HH

class IProcess;
class IAlgorithm;

class IQueue {
public:
    virtual ~IQueue() = default;
    virtual void enqueue(IProcess* process) = 0;
    virtual IProcess* dequeue() = 0;

protected:
    virtual void sort(IAlgorithm* algorithm) = 0;
};

#endif // IQUEUE_HH