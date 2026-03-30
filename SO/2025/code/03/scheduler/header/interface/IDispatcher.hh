#ifndef IDISPATCHER_HH
#define IDISPATCHER_HH

#include <vector>

class IQueue;
class IHWSimulator;

class IDispatcher {
public:
    virtual ~IDispatcher() = default;
    virtual void dispatch(IQueue* queue, IHWSimulator* hwSimulator) = 0;
    virtual void dispatch(IQueue* queue, std::vector<IHWSimulator*>& cpus) = 0;
};

#endif // IDISPATCHER_HH