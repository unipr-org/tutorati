#ifndef ALGORITHM_RR_HH
#define ALGORITHM_RR_HH

#include "IAlgorithm.hh"
#include "IPreemptive.hh"
#include "IHWSimulator.hh"
#include "IProcess.hh"
#include <list>

class AlgorithmRR : public IAlgorithm, public IPreemptive {
public:
    AlgorithmRR(int quantum);
    void sort(std::list<IProcess*>& processes) override;
    bool shouldPreempt(IHWSimulator* cpu) const override;

private:
    int quantum;
};

#endif // ALGORITHM_RR_HH
