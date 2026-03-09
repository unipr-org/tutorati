#ifndef IDISPATCHER_HH
#define IDISPATCHER_HH

class IQueue;
class IHWSimulator;

class IDispatcher {
public:
    virtual ~IDispatcher() = default;
    virtual void dispatch(IQueue* queue, IHWSimulator* hwSimulator) = 0;
};

#endif // IDISPATCHER_HH