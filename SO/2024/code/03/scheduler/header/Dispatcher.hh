#ifndef DISPATCHER_HH
#define DISPATCHER_HH

#include "IDispatcher.hh"
#include "IHWSimulator.hh"
#include "IQueue.hh"

class Dispatcher : public IDispatcher {
public:
    void dispatch(IQueue* queue, IHWSimulator* cpu) override;
};

#endif // DISPATCHER_HH
