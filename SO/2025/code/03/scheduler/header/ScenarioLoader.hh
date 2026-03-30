#ifndef SCENARIOLOADER_HH
#define SCENARIOLOADER_HH

#include <string>
#include <vector>
#include <map>

class IAlgorithm;
class IQueue;
class IScheduler;
class IDispatcher;
class IHWSimulator;
class IProcess;
class Kernel;

class ScenarioLoader {
public:
    ScenarioLoader(const std::string& scenarioPath);
    ~ScenarioLoader();

    bool load();
    void run();
    void writeResults();

private:
    std::string scenarioPath;
    std::map<std::string, std::string> config;

    // oggetti posseduti
    std::vector<IAlgorithm*> algorithms;
    std::vector<IQueue*> queues;
    IScheduler* scheduler;
    IDispatcher* dispatcher;
    std::vector<IHWSimulator*> cpuList;
    std::vector<IProcess*> processes;
    Kernel* kernel;

    bool parseConfig();
    bool parseProcesses();
    bool buildComponents();
};

#endif // SCENARIOLOADER_HH
