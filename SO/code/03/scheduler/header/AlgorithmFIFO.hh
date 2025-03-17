#ifndef FIFO_ALGORITHM_HH
#define FIFO_ALGORITHM_HH

#include "IAlgorithm.hh"
#include <list>
#include "IProcess.hh"

class AlgorithmFIFO : public IAlgorithm {
public:
    void sort(std::list<IProcess*>& processes) override;
};

#endif // FIFO_ALGORITHM_HH
