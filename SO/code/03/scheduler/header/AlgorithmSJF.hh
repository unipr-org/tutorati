#ifndef SJF_ALGORITHM_HH
#define SJF_ALGORITHM_HH

#include "IAlgorithm.hh"
#include "IProcess.hh"
#include <list>

class AlgorithmSJF : public IAlgorithm {
public:
    void sort(std::list<IProcess*>& processes) override;
};

#endif // SJF_ALGORITHM_HH
