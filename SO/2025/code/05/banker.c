#include "banker.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// strutture dati per l'algoritmo del banchiere
size_t *available;    // vettore delle risorse disponibili
size_t **maximum;     // matrice delle richieste massime
size_t **allocated;   // matrice delle risorse assegnate
size_t **need;        // matrice delle necessità residue
size_t n;             // numero di thread
size_t m;             // numero di tipi di risorse

// inizializzazione delle strutture dati
void
initialize(size_t num_threads, size_t num_resources) {
    n = num_threads;
    m = num_resources;
    
    // allocazione dei vettori e delle matrici
    available = (size_t*)malloc(m * sizeof(size_t));
    
    maximum = (size_t**)malloc(n * sizeof(size_t*));
    allocated = (size_t**)malloc(n * sizeof(size_t*));
    need = (size_t**)malloc(n * sizeof(size_t*));
    
    for (size_t i = 0; i < n; ++i) {
        maximum[i] = (size_t*)malloc(m * sizeof(size_t));
        allocated[i] = (size_t*)malloc(m * sizeof(size_t));
        need[i] = (size_t*)malloc(m * sizeof(size_t));
    }
}

// liberazione della memoria allocata
void
cleanup() {
    free(available);
    
    for (size_t i = 0; i < n; ++i) {
        free(maximum[i]);
        free(allocated[i]);
        free(need[i]);
    }
    
    free(maximum);
    free(allocated);
    free(need);
}

// calcolo della matrice delle necessità
void
calculate_need() {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }
}

// verifica se il sistema è in uno stato sicuro
bool
is_safe() {
    bool *finish = (bool*)malloc(n * sizeof(bool));
    size_t *work = (size_t*)malloc(m * sizeof(size_t));
    
    // 1. inizializza work = available e finish[i] = falso
    for (size_t i = 0; i < m; ++i) {
        work[i] = available[i];
    }
    
    for (size_t i = 0; i < n; ++i) {
        finish[i] = false;
    }
    
    size_t count = 0;
    while (count < n) {
        bool found = false;
        
        // 2. cerca un thread che può completare
        for (size_t i = 0; i < n; ++i) {
            if (finish[i] == false) {
                bool can_allocate = true;
                
                // verifica se need_i <= work
                for (size_t j = 0; j < m; ++j) {
                    // se la richiesta di risorse è maggiore delle risorse disponibili
                    // non posso allocare
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // 4. work = work + allocated_i
                    for (size_t j = 0; j < m; ++j) {
                        work[j] += allocated[i][j];
                    }
                    
                    // 5. finish[i] = vero
                    finish[i] = true;
                    ++count;
                    found = true;
                }
            }
        }
        
        // se non trovo thread che possono completare, lo stato non è sicuro
        if (!found) {
            free(finish);
            free(work);
            return false;
        }
    }
    
    // 7. se tutti i thread sono in finish[i] = vero, lo stato è sicuro
    free(finish);
    free(work);
    return true;
}

// algoritmo di richiesta risorse
bool
request_resources(size_t thread_id, size_t request[]) {
    // 1. verifica se la richiesta è valida
    for (size_t j = 0; j < m; ++j) {
        if (request[j] > need[thread_id][j]) {
            printf("errore: il thread %ld ha superato il numero massimo di richieste\n", thread_id);
            return false;
        }
    }
    
    // 2. verifica se le risorse sono disponibili
    for (size_t j = 0; j < m; ++j) {
        if (request[j] > available[j]) {
            printf("thread %ld deve attendere: risorse non disponibili\n", thread_id);
            return false;
        }
    }
    
    // 3. simula l'assegnazione delle risorse
    // salva lo stato corrente
    size_t *avail_backup = (size_t*)malloc(m * sizeof(size_t));
    size_t *alloc_backup = (size_t*)malloc(m * sizeof(size_t));
    size_t *need_backup = (size_t*)malloc(m * sizeof(size_t));
    
    for (size_t j = 0; j < m; ++j) {
        avail_backup[j] = available[j];
        alloc_backup[j] = allocated[thread_id][j];
        need_backup[j] = need[thread_id][j];
        
        // 4-6. aggiorna lo stato
        available[j] -= request[j];
        allocated[thread_id][j] += request[j];
        need[thread_id][j] -= request[j];
    }
    
    // verifica se il nuovo stato è sicuro
    if (is_safe()) {
        free(avail_backup);
        free(alloc_backup);
        free(need_backup);
        return true;
    } else {
        // ripristina lo stato precedente
        for (size_t j = 0; j < m; ++j) {
            available[j] = avail_backup[j];
            allocated[thread_id][j] = alloc_backup[j];
            need[thread_id][j] = need_backup[j];
        }
        
        printf("thread %ld deve attendere: assegnazione non sicura\n", thread_id);
        free(avail_backup);
        free(alloc_backup);
        free(need_backup);
        return false;
    }
}

// stampa lo stato del sistema
void
print_state() {
    
    printf("\n=================================================\n");
    printf("               STATO DEL SISTEMA                 \n");
    printf("=================================================\n\n");
    

    printf("Risorse disponibili: ");
    for (size_t j = 0; j < m; ++j) {
        printf("%ld ", available[j]);
    }
    printf("\n\n");
    
    printf("Allocazioni:\n");
    printf("Thread\tMax\t\tAssegnate\tNecessità\n");
    
    for (size_t i = 0; i < n; ++i) {
        printf("T%ld\t", i);
        
        for (size_t j = 0; j < m; ++j) {
            printf("%ld ", maximum[i][j]);
        }
        printf("\t");
        
        for (size_t j = 0; j < m; ++j) {
            printf("%ld ", allocated[i][j]);
        }
        printf("\t");
        
        for (size_t j = 0; j < m; ++j) {
            printf("%ld ", need[i][j]);
        }
        printf("\n");
    }
}