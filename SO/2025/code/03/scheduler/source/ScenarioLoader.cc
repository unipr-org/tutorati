#include "ScenarioLoader.hh"
#include "Kernel.hh"
#include "Scheduler.hh"
#include "ReadyQueue.hh"
#include "Dispatcher.hh"
#include "CpuSimulator.hh"
#include "AlgorithmFIFO.hh"
#include "AlgorithmSJF.hh"
#include "AlgorithmRR.hh"
#include "MultilevelQueue.hh"
#include "Process.hh"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

ScenarioLoader::ScenarioLoader(const std::string& scenarioPath)
    : scenarioPath(scenarioPath), scheduler(nullptr), dispatcher(nullptr), kernel(nullptr) {}

ScenarioLoader::~ScenarioLoader() {
    delete kernel;
    delete dispatcher;
    delete scheduler;
    for (IHWSimulator* cpu : cpuList) delete cpu;
    for (IQueue* q : queues) delete q;
    for (IAlgorithm* a : algorithms) delete a;
    for (IProcess* p : processes) delete p;
}

bool ScenarioLoader::load() {
    if (!parseConfig()) return false;
    if (!parseProcesses()) return false;
    return buildComponents();
}

bool ScenarioLoader::parseConfig() {
    std::ifstream file(scenarioPath + "/config.cfg");
    if (!file.is_open()) {
        std::cerr << "Errore: impossibile aprire " << scenarioPath << "/config.cfg" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // ignora commenti e linee vuote
        if (line.empty() || line[0] == '#') continue;

        // rimuovi spazi
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        size_t eq = line.find('=');
        if (eq != std::string::npos) {
            std::string key = line.substr(0, eq);
            std::string value = line.substr(eq + 1);
            config[key] = value;
        }
    }
    return true;
}

bool ScenarioLoader::parseProcesses() {
    std::ifstream file(scenarioPath + "/processes.csv");
    if (!file.is_open()) {
        std::cerr << "Errore: impossibile aprire " << scenarioPath << "/processes.csv" << std::endl;
        return false;
    }

    std::string line;
    // leggi header
    if (!std::getline(file, line)) return false;

    // determina se c'è colonna priority
    bool hasPriority = (line.find("priority") != std::string::npos);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, burstStr, arrivalStr, priorityStr;

        std::getline(ss, id, ',');
        std::getline(ss, burstStr, ',');
        std::getline(ss, arrivalStr, ',');

        int burst = std::stoi(burstStr);
        int arrival = std::stoi(arrivalStr);
        int priority = 0;

        if (hasPriority && std::getline(ss, priorityStr, ',')) {
            priority = std::stoi(priorityStr);
        }

        processes.push_back(new Process(id, burst, priority, arrival));
    }
    return true;
}

bool ScenarioLoader::buildComponents() {
    int cores = 1;
    if (config.count("cores")) {
        cores = std::stoi(config["cores"]);
    }

    std::string algo = config["algorithm"];

    dispatcher = new Dispatcher();

    if (algo == "fifo") {
        IAlgorithm* alg = new AlgorithmFIFO();
        algorithms.push_back(alg);
        IQueue* q = new ReadyQueue(alg);
        queues.push_back(q);
        scheduler = new Scheduler(q);

        for (int i = 0; i < cores; i++) cpuList.push_back(new CpuSimulator());
        kernel = new Kernel(scheduler, q, cpuList, dispatcher);

    } else if (algo == "sjf") {
        IAlgorithm* alg = new AlgorithmSJF();
        algorithms.push_back(alg);
        IQueue* q = new ReadyQueue(alg);
        queues.push_back(q);
        scheduler = new Scheduler(q);

        for (int i = 0; i < cores; i++) cpuList.push_back(new CpuSimulator());
        kernel = new Kernel(scheduler, q, cpuList, dispatcher);

    } else if (algo == "rr") {
        int quantum = 2;
        if (config.count("quantum")) {
            quantum = std::stoi(config["quantum"]);
        }
        AlgorithmRR* alg = new AlgorithmRR(quantum);
        algorithms.push_back(alg);
        IQueue* q = new ReadyQueue(alg);
        queues.push_back(q);
        scheduler = new Scheduler(q);

        for (int i = 0; i < cores; i++) cpuList.push_back(new CpuSimulator());
        kernel = new Kernel(scheduler, q, cpuList, dispatcher, alg);

    } else if (algo == "mlq") {
        int levels = 2;
        if (config.count("mlq_levels")) {
            levels = std::stoi(config["mlq_levels"]);
        }

        MultilevelQueue* mlq = new MultilevelQueue();
        queues.push_back(mlq);

        IAlgorithm* preemptionAlg = nullptr;

        for (int i = 0; i < levels; i++) {
            std::string prefix = "mlq_" + std::to_string(i) + "_";
            std::string levelAlgo = config[prefix + "algorithm"];

            IAlgorithm* levelAlg = nullptr;
            if (levelAlgo == "rr") {
                int q = 2;
                if (config.count(prefix + "quantum")) {
                    q = std::stoi(config[prefix + "quantum"]);
                }
                AlgorithmRR* rrAlg = new AlgorithmRR(q);
                levelAlg = rrAlg;
                if (i == 0) preemptionAlg = rrAlg; // preemption dalla coda più alta
            } else if (levelAlgo == "sjf") {
                levelAlg = new AlgorithmSJF();
            } else {
                levelAlg = new AlgorithmFIFO();
            }
            algorithms.push_back(levelAlg);

            IQueue* levelQueue = new ReadyQueue(levelAlg);
            queues.push_back(levelQueue);
            mlq->addQueue(i, levelQueue);
        }

        scheduler = new Scheduler(mlq);

        for (int i = 0; i < cores; i++) cpuList.push_back(new CpuSimulator());
        kernel = new Kernel(scheduler, mlq, cpuList, dispatcher, preemptionAlg);

    } else {
        std::cerr << "Errore: algoritmo sconosciuto '" << algo << "'" << std::endl;
        return false;
    }

    // aggiungi processi come pending
    for (IProcess* p : processes) {
        kernel->addPendingProcess(p);
    }

    return true;
}

void ScenarioLoader::run() {
    kernel->runUntilComplete();
}

void ScenarioLoader::writeResults() {
    const std::map<std::string, ProcessStats>& stats = kernel->getStats();
    const std::vector<GanttRow>& gantt = kernel->getGanttLog();
    int totalTicks = kernel->getTotalTicks();

    // scrivi results.csv
    {
        std::ofstream file(scenarioPath + "/results.csv");
        file << "id,arrival,burst,start,completion,turnaround,waiting,response" << std::endl;

        int numCpus = (int)cpuList.size();

        // calcola utilizzo per CPU
        std::vector<int> cpuBusy(numCpus, 0);
        for (size_t i = 0; i < gantt.size(); i++) {
            for (int c = 0; c < numCpus; c++) {
                if (gantt[i].cpuAssignments[c] != "-") {
                    cpuBusy[c]++;
                }
            }
        }

        for (std::map<std::string, ProcessStats>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
            const std::string& id = it->first;
            const ProcessStats& s = it->second;
            int turnaround = s.completionTime - s.arrivalTime;
            int waiting = turnaround - s.burstTime;
            int response = s.startTime - s.arrivalTime;
            file << id << "," << s.arrivalTime << "," << s.burstTime << ","
                 << s.startTime << "," << s.completionTime << ","
                 << turnaround << "," << waiting << "," << response << std::endl;
        }

        // commenti con utilizzo CPU
        double avgUtil = 0;
        for (int c = 0; c < numCpus; c++) {
            double util = (totalTicks > 0) ? (100.0 * cpuBusy[c] / totalTicks) : 0;
            file << "# cpu_" << c << "_utilization=" << std::fixed << std::setprecision(1) << util << std::endl;
            avgUtil += util;
        }
        avgUtil /= numCpus;
        file << "# avg_utilization=" << std::fixed << std::setprecision(1) << avgUtil << std::endl;
    }

    // scrivi gantt.csv
    {
        std::ofstream file(scenarioPath + "/gantt.csv");
        int numCpus = (int)cpuList.size();

        // header
        file << "tick";
        for (int c = 0; c < numCpus; c++) {
            file << ",cpu_" << c;
        }
        file << std::endl;

        // righe
        for (size_t i = 0; i < gantt.size(); i++) {
            file << gantt[i].tick;
            for (int c = 0; c < numCpus; c++) {
                file << "," << gantt[i].cpuAssignments[c];
            }
            file << std::endl;
        }
    }

    std::cout << "Risultati scritti in " << scenarioPath << "/results.csv e gantt.csv" << std::endl;
}
