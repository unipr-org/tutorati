#include <stdio.h>
#include "banker.h"


// esempio libro di testo
void
example() {
    initialize(5, 3);
        
    // inizializzazione del vettore delle risorse disponibili
    // available[0] = 10;
    // available[1] = 5;
    // available[2] = 7;

    
    // per partire già con uno stato del sistema già inizializzato
    available[0] = 3;
    available[1] = 3;
    available[2] = 2;

    // inizializzazione della matrice maximum
    size_t max_claim[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // inizializzazione della matrice allocated
    size_t allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // copia dei valori nelle matrici
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            maximum[i][j] = max_claim[i][j];
            allocated[i][j] = allocation[i][j];
        }
    }

    // calcola della matrice delle necessità
    calculate_need();

    // stampa lo stato iniziale
    print_state();

    // verifica se lo stato iniziale è sicuro
    if (is_safe()) {
        printf("\nLo stato iniziale è sicuro.\n");
    } else {
        printf("\nATTENZIONE: Lo stato iniziale NON è sicuro!\n");
    }
    
    printf("\n=================================================\n");
    printf("          TEST RICHIESTA RISORSE                 \n");
    printf("=================================================\n");
    

    // test di una richiesta di risorse
    printf("\n--- Test richiesta risorse ---\n");
    {
        size_t thread_id = 1;
        size_t request[3] = {1, 0, 2};

        printf("Thread T%ld richiede risorse: (%ld, %ld, %ld)\n", 
            thread_id, request[0], request[1], request[2]);

        if (request_resources(thread_id, request)) {
            printf("Richiesta accettata!\n");
            print_state();
        } else {
            printf("Richiesta rifiutata.\n");
        }
    }

    // test di una richiesta di risorse non sicura
    {
        printf("\n--- Test richiesta risorse non valida ---\n");
        size_t thread_id = 4;
        size_t request[3] = {3, 3, 0};

        printf("Thread T%ld richiede risorse: (%ld, %ld, %ld)\n", 
            thread_id, request[0], request[1], request[2]);
        if (request_resources(thread_id, request)) {
            printf("Richiesta accettata!\n");
            print_state();
        } else {
            printf("Richiesta rifiutata.\n");
        }
    }
    // test di una richiesta di risorse che sembra sicura
    {
        printf("\n--- Test richiesta risorse ---\n");
        size_t thread_id = 0;
        size_t request2[3] = {0, 2, 0};
        printf("Thread T%ld richiede risorse: (%ld, %ld, %ld)\n",
            thread_id, request2[0], request2[1], request2[2]);
        
            if (request_resources(thread_id, request2)) {
            printf("Richiesta accettata!\n");
            print_state();
        } else {
            printf("Richiesta rifiutata.\n");
        }
    }

    cleanup();
}



int
main() {
    example();
    
    return 0;
}