#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

void
readFile(char* filename, int** matrix,
    const size_t rows, const size_t cols) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            fscanf(file, "%d", &matrix[r][c]);
            // Consuma un carattere ',' o '\n'
            fgetc(file);
        }
    }
    fclose(file);
}

// Struct per passare i dati ai thread
typedef struct {
    int **matrix;
    size_t nRows;
    size_t startCol;
    size_t steps;
    long *ress;
    size_t index;
} thread_data_t;



// Funzione del thread
void*
thread_routine(void *arg) {

    printf("Thread %ld inizializzato\n", pthread_self());

    thread_data_t *data = (thread_data_t *) arg;
    long sum = 0;
    size_t nrows = data->nRows;
    size_t startCol = data->startCol;
    size_t steps = data->steps;
    int** matrix = data->matrix;
    long* ress = data->ress;
    size_t index = data->index;

    // Calcolo della somma parziale per le colonne assegnate
    for (size_t r = 0; r < nrows; ++r) {
        for (size_t c = startCol; c < startCol + steps; ++c) {
            sum += matrix[r][c];
        }
    }

    ress[index] = sum;
    printf("Thread %ld lavoro completato\n", pthread_self());

    pthread_exit(NULL);
}


int
main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Usage: %s <filename> <num_righe> <num_colonne>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char* filename = argv[1];
    size_t rows = atoi(argv[2]);
    size_t cols = atoi(argv[3]);

    // Allocazione della matrice
    int **matrix = calloc(rows, sizeof(int*));
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = calloc(cols, sizeof(int));
    }

    // Lettura da file
    readFile(filename, matrix, rows, cols);

    // Stampa della matrice
    
    // for (size_t i = 0; i < rows; ++i) {
    //     for (size_t j = 0; j < cols; ++j) {
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    size_t nthreads;
    printf("Inserisci il numero dei thread: ");
    scanf("%zu", &nthreads);
    printf("Numero di thread: %zu \n", nthreads);

    pthread_t *threads = malloc(nthreads * sizeof(pthread_t));

    // Allocazione di un array di struct per i dati che verranno passati a ciascun thread
    thread_data_t *tdata = malloc(nthreads * sizeof(thread_data_t));
    
    // Allocazione di un array per le somme parziali
    long *ress = malloc(nthreads * sizeof(long));
    int cols_per_thread = cols / nthreads;
    int remain = cols % nthreads;


    for (size_t i = 0; i < nthreads; ++i) {
        tdata[i].matrix = matrix;
        tdata[i].nRows = rows;
        tdata[i].startCol = i * cols_per_thread;

        // Se è l'ultimo thread, aggiunge il resto delle colonne
        tdata[i].steps = (i == nthreads - 1) ? cols_per_thread + remain : cols_per_thread;
        tdata[i].ress = ress;
        tdata[i].index = i;

        if (pthread_create(&threads[i], NULL, thread_routine, (void *) &tdata[i]) != 0) {
            perror("Errore nella creazione del thread");
            exit(EXIT_FAILURE);
        }
    }

    // Attende il termine di tutti i thread
    for (size_t i = 0; i < nthreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    long sum = 0;
    for (size_t i = 0; i < nthreads; ++i) {
        sum += ress[i];
    }

    printf("Somma: %ld\n", sum);


    for (size_t i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(threads);
    free(tdata);
    free(ress);

    return EXIT_SUCCESS;
}
