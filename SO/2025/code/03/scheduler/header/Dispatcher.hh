#ifndef DISPATCHER_HH
#define DISPATCHER_HH

#include "IDispatcher.hh"
#include "IHWSimulator.hh"
#include "IQueue.hh"
#include <vector>

class Dispatcher : public IDispatcher {
public:
    void dispatch(IQueue* queue, IHWSimulator* cpu) override;
    void dispatch(IQueue* queue, std::vector<IHWSimulator*>& cpus) override;
};

#endif // DISPATCHER_HH
