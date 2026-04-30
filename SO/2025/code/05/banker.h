#ifndef BANKER_H
#define BANKER_H

#include <stdbool.h>
#include <stddef.h>

// strutture dati per l'algoritmo del banchiere
extern size_t* available;    // vettore delle risorse disponibili
extern size_t** maximum;     // matrice delle richieste massime
extern size_t** allocated;   // matrice delle risorse assegnate
extern size_t** need;        // matrice delle necessità residue
extern size_t n;             // numero di thread
extern size_t m;             // numero di tipi di risorse

// inizializzazione delle strutture dati
void
initialize(size_t num_threads, size_t num_resources);

// liberazione della memoria allocata
void
cleanup();

// calcolo della matrice delle necessità
void
calculate_need();

// verifica se il sistema è in uno stato sicuro
bool
is_safe();

// algoritmo di richiesta risorse
bool
request_resources(size_t thread_id, size_t request[]);

// stampa lo stato del sistema
void
print_state();

#endif // BANKER_H