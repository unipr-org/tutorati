#!/bin/bash

if [ $# -ne 4 ]; then
    echo "Uso: $0 <numero_scenario> <min_page_ref> <max_page_ref> <step>"
    echo "Esempio: $0 1 10000 100000 10000"
    exit 1
fi

SCENARIO_NUM=$1
MIN_PAGE_REF=$2
MAX_PAGE_REF=$3
STEP=$4

SCENARIOS_FILE="scenarios.md"
COMPILE_SCRIPT="./compile.sh"
PAGE_FOLDER="./pages"
BIN_FOLDER="$PAGE_FOLDER/bin/"
CSV_FILE="scenario_${SCENARIO_NUM}_results.csv"
PLOT_SCRIPT="plot_res.py"
PLOT_FOLDER="./plots/"

if [ ! -f "$SCENARIOS_FILE" ]; then
    echo "Errore: file $SCENARIOS_FILE non trovato."
    exit 1
fi

# estrai i parametri dello scenario specificato
PARAMETERS=$(awk -v scenario="# Scenario $SCENARIO_NUM" '
    $0 ~ scenario {found=1} 
    found && /^## Parametri/ {start=1; next} 
    start && /^## / {exit} 
    start {print}' "$SCENARIOS_FILE")

if [ -z "$PARAMETERS" ]; then
    echo "Errore: scenario $SCENARIO_NUM non trovato o privo di parametri."
    exit 1
fi

# inizializza i flag per il comando compile.sh
FLAGS=""
while IFS= read -r line; do
    # estrai nome e valore del parametro
    if [[ $line =~ ^([A-Z_]+)\ *=\ *([0-9]+) ]]; then
        PARAM_NAME=${BASH_REMATCH[1]}
        PARAM_VALUE=${BASH_REMATCH[2]}
        FLAGS="$FLAGS -D$PARAM_NAME=$PARAM_VALUE"
    fi
done <<< "$PARAMETERS"

# esegui il file compile.sh con i flag estratti
cd $PAGE_FOLDER
if [ -x "$COMPILE_SCRIPT" ]; then
    echo "Eseguo $COMPILE_SCRIPT con i flag:\n$FLAGS"
    $COMPILE_SCRIPT $FLAGS
else
    echo "Errore: script $COMPILE_SCRIPT non trovato o non eseguibile."
    exit 1
fi
cd ..

# crea il file CSV e aggiungi l'intestazione
echo "nome_programma,page_ref,page_faults" > "$CSV_FILE"

# esegui tutti gli script sotto $BIN_FOLDER per ogni valore di page_ref
for ((PAGE_REF=MIN_PAGE_REF; PAGE_REF<=MAX_PAGE_REF; PAGE_REF+=STEP)); do

    for PROGRAM in "$BIN_FOLDER"*; do
        if [ -x "$PROGRAM" ]; then
            echo "Eseguo $PROGRAM con parametro $PAGE_REF..."
            OUTPUT=$("$PROGRAM" "$PAGE_REF")
            echo "Output di $PROGRAM:"
            echo "$OUTPUT"
            
            # estrai il valore di page_faults dall'output
            PAGE_FAULTS=$(echo "$OUTPUT" | grep -oP 'page_faults\s*=\s*\K[0-9]+')
            
            if [ -n "$PAGE_FAULTS" ]; then
                # aggiungi i risultati al file CSV
                PROGRAM_NAME=$(basename "$PROGRAM")
                echo "$PROGRAM_NAME,$PAGE_REF,$PAGE_FAULTS" >> "$CSV_FILE"
            else
                echo "Errore: impossibile trovare 'page_faults' nell'output di $PROGRAM"
            fi
        else
            echo "Errore: $PROGRAM non è eseguibile."
        fi
    done
done

# creazione cartella plots
if [ ! -d "$PLOT_FOLDER" ]; then
    mkdir "$PLOT_FOLDER"
else
    rm -rf "$PLOT_FOLDER"/*
fi

# plot
if [ -e "$PLOT_SCRIPT" ]; then
    echo "Lancio $PLOT_SCRIPT per generare il plot..."
    python3 "$PLOT_SCRIPT" "$CSV_FILE" "$PLOT_FOLDER"
else
    echo "Errore: script $PLOT_SCRIPT non trovato o non eseguibile."
    exit 1
fi