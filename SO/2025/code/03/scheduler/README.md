# Mini Scheduler

Simulatore di scheduling CPU con supporto per algoritmi FIFO, SJF, Round Robin, Multilevel Queue e multi-core.

## Compilazione

Compilazione senza stampe:

```bash
make
```

Compilazione con stampe di debug:

```bash
make DEBUG=1
```

## Esecuzione

Eseguire tutte le demo:

```bash
./scheduler
```

Eseguire una demo specifica:

```bash
./scheduler fifo|sjf|rr|mlq|multicore
```

## Scenari

Gli scenari permettono di definire processi e configurazione da file, eseguire la simulazione e raccogliere metriche (turnaround, waiting, response time) e diagrammi di Gantt.

### Struttura di uno scenario

```
scenarios/
  nome_scenario/
    processes.csv    # input: processi da simulare
    config.cfg       # input: configurazione algoritmo e core
    results.csv      # output: metriche per processo
    gantt.csv        # output: assegnamenti CPU per tick
```

### processes.csv

```csv
id,burst,arrival,priority
A,5,0,0
B,3,2,1
C,4,4,0
```

La colonna `priority` e' opzionale (default 0).

### config.cfg

```ini
# Algoritmo semplice
cores=2
algorithm=rr
quantum=3

# Multilevel Queue
cores=1
algorithm=mlq
mlq_levels=2
mlq_0_algorithm=rr
mlq_0_quantum=2
mlq_1_algorithm=fifo
```

Valori `algorithm`: `fifo`, `sjf`, `rr`, `mlq`.

### Esecuzione di uno scenario

```bash
./scheduler --scenario scenarios/fifo_basic
```

Genera `results.csv` e `gantt.csv` nella cartella dello scenario.

### Script Python per analisi e plot

```bash
python3 scenarios.py fifo_basic rr_multicore
```

Per ogni scenario genera:
- Tabella ASCII con metriche nel terminale
- `gantt.png` — diagramma di Gantt colorato per processo
- `metrics.png` — bar chart turnaround/waiting/response per processo

Se vengono passati piu' scenari, genera anche `scenarios/comparison.png` con medie a confronto.

Dipendenze: `matplotlib`, `numpy`.

### Scenari di esempio

| Scenario | Algoritmo | Core | Descrizione |
|----------|-----------|------|-------------|
| `fifo_basic` | FIFO | 1 | 3 processi con arrival time diversi |
| `rr_multicore` | Round Robin (q=2) | 2 | 4 processi su 2 core |

### Scenari di confronto

Sotto `scenarios/comparison/` sono presenti scenari che confrontano tutti gli algoritmi sugli stessi 5 processi (A-E), divisi in single-core e multi-core.

Processi comuni: `A(6,0,0)`, `B(4,1,1)`, `C(8,2,2)`, `D(3,4,3)`, `E(5,6,1)` — formato `(burst, arrival, priority)`.

#### Single-core (`comparison/single/`)

| Scenario | Algoritmo | Configurazione |
|----------|-----------|----------------|
| `comparison/single/fifo` | FIFO | 1 core |
| `comparison/single/sjf` | SJF | 1 core |
| `comparison/single/rr` | Round Robin | 1 core, quantum=3 |
| `comparison/single/mlq` | Multilevel Queue | 1 core, 4 livelli (RR+FIFO) |

#### Multi-core (`comparison/multi/`)

| Scenario | Algoritmo | Configurazione |
|----------|-----------|----------------|
| `comparison/multi/fifo` | FIFO | 4 core |
| `comparison/multi/sjf` | SJF | 4 core |
| `comparison/multi/rr` | Round Robin | 4 core, quantum=3 |
| `comparison/multi/mlq` | Multilevel Queue | 4 core, 4 livelli (RR+FIFO) |

#### Esecuzione confronto

```bash
# Eseguire tutti gli scenari di confronto
for dir in scenarios/comparison/single/* scenarios/comparison/multi/*; do
  ./scheduler --scenario "$dir"
done

# Generare plot comparativi
python3 scenarios.py comparison/single/fifo comparison/single/sjf comparison/single/rr comparison/single/mlq
python3 scenarios.py comparison/multi/fifo comparison/multi/sjf comparison/multi/rr comparison/multi/mlq
```

## Diagrammi

### Class Diagram

```mermaid
classDiagram
    class IProcess {
        <<interface>>
        +getName() string
        +getRemainingTime() int
        +getTotalTime() int
        +getPriority() int
        +getArrivalTime() int
        +tick() void
        #incrementPC() void
    }

    class IHWSimulator {
        <<interface>>
        +set(IProcess*) void
        +unset() IProcess*
        +isFree() bool
        +tick() void
        +getRunningTicks() int
        +getCurrentProcess() IProcess*
    }

    class IQueue {
        <<interface>>
        +enqueue(IProcess*) void
        +dequeue() IProcess*
        #sort(IAlgorithm*) void
    }

    class IAlgorithm {
        <<interface>>
        +sort(list~IProcess*~) void
    }

    class IPreemptive {
        <<interface>>
        +shouldPreempt(IHWSimulator*) bool
    }

    class IScheduler {
        <<interface>>
        +add(IProcess*) void
    }

    class IDispatcher {
        <<interface>>
        +dispatch(IQueue*, IHWSimulator*) void
        +dispatch(IQueue*, vector~IHWSimulator*~) void
    }

    class Process {
        -name : string
        -totalTime : int
        -remainingTime : int
        -priority : int
        -arrivalTime : int
        +Process(name, burstTime, priority, arrivalTime)
    }

    class CpuSimulator {
        -currentProcess : IProcess*
        -runningTicks : int
    }

    class ReadyQueue {
        -processes : list~IProcess*~
        -alg : IAlgorithm*
    }

    class MultilevelQueue {
        -queues : map~int, IQueue*~
        +addQueue(priority, IQueue*) void
    }

    class AlgorithmFIFO
    class AlgorithmSJF
    class AlgorithmRR {
        -quantum : int
        +AlgorithmRR(quantum)
    }

    class Scheduler {
        -queue : IQueue*
    }

    class Dispatcher

    class ProcessStats {
        +arrivalTime : int
        +burstTime : int
        +startTime : int
        +completionTime : int
    }

    class GanttRow {
        +tick : int
        +cpuAssignments : vector~string~
    }

    class Kernel {
        -scheduler : IScheduler*
        -queue : IQueue*
        -cpus : vector~IHWSimulator*~
        -dispatcher : IDispatcher*
        -algorithm : IAlgorithm*
        -processStats : map~string, ProcessStats~
        -ganttLog : vector~GanttRow~
        +addProcess(IProcess*) void
        +run(numTicks) void
        +addPendingProcess(IProcess*) void
        +runUntilComplete() void
        +getStats() map~string, ProcessStats~
        +getGanttLog() vector~GanttRow~
        +getTotalTicks() int
    }

    class ScenarioLoader {
        -scenarioPath : string
        -config : map~string, string~
        +ScenarioLoader(scenarioPath)
        +load() bool
        +run() void
        +writeResults() void
    }

    IProcess <|.. Process
    IHWSimulator <|.. CpuSimulator
    IQueue <|.. ReadyQueue
    IQueue <|.. MultilevelQueue
    IAlgorithm <|.. AlgorithmFIFO
    IAlgorithm <|.. AlgorithmSJF
    IAlgorithm <|.. AlgorithmRR
    IPreemptive <|.. AlgorithmRR
    IScheduler <|.. Scheduler
    IDispatcher <|.. Dispatcher

    Kernel --> IScheduler
    Kernel --> IQueue
    Kernel --> IHWSimulator
    Kernel --> IDispatcher
    Kernel --> IAlgorithm
    ReadyQueue --> IAlgorithm
    MultilevelQueue --> IQueue
    Scheduler --> IQueue
    Kernel --> ProcessStats
    Kernel --> GanttRow
    ScenarioLoader --> Kernel
```

### Component Diagram

```mermaid
flowchart LR
    subgraph Kernel
        direction TB
        K[Kernel::run]
    end

    subgraph Scheduling
        S[Scheduler]
        Q[Queue]
        A[Algorithm]
    end

    subgraph Execution
        D[Dispatcher]
        CPU1[CPU 0]
        CPU2[CPU 1]
    end

    P([Processi]) --> S
    S -->|enqueue| Q
    A -->|sort| Q
    K -->|preemption check| CPU1
    K -->|preemption check| CPU2
    K -->|re-enqueue| Q
    K -->|dispatch| D
    D -->|dequeue| Q
    D -->|set| CPU1
    D -->|set| CPU2
```

### Sequence Diagram — Esecuzione con Preemption (Round Robin, quantum=2)

```mermaid
sequenceDiagram
    participant K as Kernel
    participant P as IPreemptive
    participant Q as Queue
    participant D as Dispatcher
    participant CPU as CpuSimulator

    Note over K: Tick 1
    K->>CPU: isFree()
    CPU-->>K: true (nessun check preemption)
    K->>D: dispatch(queue, cpus)
    D->>Q: dequeue()
    Q-->>D: Processo A
    D->>CPU: set(A)
    K->>CPU: tick()
    Note over CPU: A esegue (runningTicks=1)

    Note over K: Tick 2
    K->>P: shouldPreempt(cpu)
    P->>CPU: getRunningTicks()
    CPU-->>P: 1
    P-->>K: false (1 < 2)
    K->>D: dispatch(queue, cpus)
    K->>CPU: tick()
    Note over CPU: A esegue (runningTicks=2)

    Note over K: Tick 3
    K->>P: shouldPreempt(cpu)
    P->>CPU: getRunningTicks()
    CPU-->>P: 2
    P-->>K: true (2 >= 2)
    K->>CPU: unset()
    CPU-->>K: Processo A
    K->>Q: enqueue(A)
    K->>D: dispatch(queue, cpus)
    D->>Q: dequeue()
    Q-->>D: Processo B
    D->>CPU: set(B)
    K->>CPU: tick()
    Note over CPU: B esegue (runningTicks=1)
```
