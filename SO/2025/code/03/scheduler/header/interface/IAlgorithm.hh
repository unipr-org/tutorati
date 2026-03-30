#ifndef IALGORITHM_HH
#define IALGORITHM_HH

#include <list>

class IProcess;

class IAlgorithm {
public:
    virtual ~IAlgorithm() = default;
    virtual void sort(std::list<IProcess*>& processes) = 0;
};

#endif // IALGORITHM_HH