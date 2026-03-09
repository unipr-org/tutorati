# Scenari

È possibile visualizzare la lista degli scenari nel file `scenarios.md`.
Per eseguire uno scenario e produrre i plot corrispondenti, eseguire i seguenti comandi:

Creazione ambiente virtuale
```bash
python3 -m venv venv
```

Attivazione ambiente virtuale
```bash
source venv/bin/activate
```

Installazione dipendenze
```bash
pip install -r requirements.txt
```

Esecuzione di uno scenario
```bash
bash scenario.sh <scenario_number> <min_page_references> <max_page_references> <step>
```


Rimozione delle dipendenze
```bash
deactivate
bash clean.sh
```


Per aggiungere uno scenario, aggiungere una nuova sezione `# Scenario X` al file `scenarios.md` e una rispettiva sottosezione al file `## Parametri`.

es:
```bash
NUM_FRAMES = 256
NUM_PAGES = 1024 (o superiore)
PAGE_SIZE = 2048
MAX_LOCALITY_SIZE = 128
NUM_REFERENCES_IN_QUANTUM = 4000
```
