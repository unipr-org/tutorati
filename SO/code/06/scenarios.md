# Scenario 1

## Obiettivo
Dimostrare un'elevata località degli accessi per ridurre i page fault.

## Descrizione
Simulazione in cui il programma utilizza ripetutamente una porzione limitata dello spazio di indirizzamento, sfruttando fortemente la località spaziale e temporale.

## Da osservare
- Bassa frequenza di page fault.
- Elevato numero di hit grazie al prefetching.
- Il working set rimane stabile e ben definito.

## Parametri

NUM_FRAMES = 128
NUM_PAGES = 2048
PAGE_SIZE = 4096
MAX_LOCALITY_SIZE = 64 (NUM_FRAMES / 2)
NUM_REFERENCES_IN_QUANTUM = 1000

## Descrizione parametri

**NUM_FRAMES:**
Numero di frame (blocchi di memoria fisica) disponibili per l'allocazione.

**NUM_PAGES:**
Numero totale di pagine nella memoria virtuale; deve essere maggiore o uguale a NUM_FRAMES.

**PAGE_SIZE:**
Dimensione di ogni pagina in byte.

**MAX_LOCALITY_SIZE:**
Massima estensione per considerare accessi "locali". Impostato come metà del numero di frame per enfatizzare la località.

**NUM_REFERENCES_IN_QUANTUM:**
Numero di riferimenti che vengono simulati in un singolo ciclo (quantum).

---

# Scenario 2

## Obiettivo
Simulare una situazione in cui gli accessi sono distribuiti in maniera non locale.

## Descrizione
Accessi sparsi e poco prevedibili, con una bassa incidenza di località spaziale e temporale, che portano a frequenti page fault.

## Da osservare
- Aumento dei page fault.
- Maggiore frequenza nelle sostituzioni delle pagine.
- Prestazioni inferiori a causa della scarsità di pattern locali.

## Parametri

NUM_FRAMES = 128
NUM_PAGES = 2048
PAGE_SIZE = 4096
MAX_LOCALITY_SIZE = 16 (comunque uin valore piccolo)
NUM_REFERENCES_IN_QUANTUM = 1000

## Descrizione parametri

**NUM_FRAMES:**
Numero di frame disponibili per la memoria fisica.

**NUM_PAGES:**
Numero totale di pagine nella memoria virtuale.

**PAGE_SIZE:**
Dimensione di ciascuna pagina in byte.

**MAX_LOCALITY_SIZE:**
Intervallo massimo per cui gli accessi sono considerati "locali". Un valore ridotto limita il numero di pagine vicine considerate, simulando una bassa località.

**NUM_REFERENCES_IN_QUANTUM:**
Numero di riferimenti alla memoria simulati per ogni ciclo.

---

# Scenario 3

## Obiettivo
Esaminare l'effetto del limite massimo di riferimenti per pagina (MAX_REFERENCES_IN_PAGE).

## Descrizione
Simulazione mirata a saturare il contatore di riferimenti di una pagina, osservando come il limite influisce sugli algoritmi di sostituzione.

## Da osservare
- Comportamento quando una pagina raggiunge il valore massimo di riferimenti.
- Impatto sui contatori e sulla decisione di mantenere o sostituire la pagina.
- Stabilità nel riconoscere le pagine “calde” (molto referenziate).

## Parametri

PAGE_SIZE = 4096
MAX_REFERENCES_IN_PAGE = 512 (PAGE_SIZE / 8)
NUM_REFERENCES_IN_QUANTUM = 2000

## Descrizione parametri

**PAGE_SIZE:**
Dimensione di ogni pagina in byte.

**MAX_REFERENCES_IN_PAGE:**
Numero massimo di riferimenti contabili per ogni pagina in un intervallo; impedisce la crescita indefinita del contatore.

**NUM_REFERENCES_IN_QUANTUM:**
Numero di riferimenti per quantum; un valore elevato permette di saturare rapidamente il contatore di una pagina.

---

# Scenario 4

## Obiettivo
Simulare un ambiente con carico di lavoro intensivo per testare la robustezza del sistema di sostituzione delle pagine.

## Descrizione
Il simulatore gestisce un numero elevato di riferimenti in ogni quantum, costringendo il sistema a operare sotto carico elevato e verificare la gestione del working set.

## Da osservare
- Frequenza e pattern dei page fault.
- Risposta del sistema in termini di sostituzioni di pagine.
- Comportamento dei contatori di riferimento sotto carico intenso.

## Parametri

NUM_FRAMES = 128
NUM_PAGES = 2048
PAGE_SIZE = 4096
MAX_LOCALITY_SIZE = 64
NUM_REFERENCES_IN_QUANTUM = 10000

## Descrizione parametri

**NUM_FRAMES:**
Numero di frame fisici disponibili.

**NUM_PAGES:**
Numero totale di pagine nella memoria virtuale.

**PAGE_SIZE:**
Dimensione in byte di ogni pagina.

**MAX_LOCALITY_SIZE:**
Valore che definisce l'estensione della località; mantenuto a un livello medio per osservare il comportamento in presenza di un carico intenso.

**NUM_REFERENCES_IN_QUANTUM:**
Numero di accessi alla memoria simulati in un quantum, elevato per simulare un carico intensivo.

---

# Scenario 5

## Obiettivo
Testare la gestione del sistema in una condizione di overcommit della memoria virtuale.

## Descrizione
Il sistema deve gestire un numero molto elevato di pagine virtuali rispetto ai frame fisici, enfatizzando il ruolo dell'algoritmo di sostituzione nel riconoscere il working set attivo.

## Da osservare
- Frequenza dei page fault in presenza di numerose pagine virtuali.
- Efficacia dell'algoritmo di sostituzione nel mantenere in memoria le pagine utili.
- Dinamica di gestione del working set in condizioni di alta pressione.

## Parametri

NUM_FRAMES = 128
NUM_PAGES = 4096 (o superiore)
PAGE_SIZE = 4096
MAX_LOCALITY_SIZE = 64
NUM_REFERENCES_IN_QUANTUM = 1000

## Descrizione parametri

**NUM_FRAMES:**
Numero di frame disponibili per l'allocazione fisica della memoria.

**NUM_PAGES:**
Numero totale di pagine nella memoria virtuale, aumentato per simulare un ambiente di overcommit.

**PAGE_SIZE:**
Dimensione in byte di ciascuna pagina.

**MAX_LOCALITY_SIZE:**
Definisce l'intervallo di località spaziale; un valore medio che permette di osservare il comportamento in presenza di molti indirizzi virtuali.

**NUM_REFERENCES_IN_QUANTUM:**
Numero di riferimenti alla memoria simulati per ogni ciclo, mantenuto standard per evidenziare il comportamento con un alto numero di pagine virtuali.
