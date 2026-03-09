#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdbool.h>
#include <sys/shm.h> 


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
            // consuma un carattere ',' o '\n'
            char c = fgetc(file);
        }
    }

    fclose(file);
}



void
child(int** matrix, const size_t nRows, const size_t startCol,
    const size_t steps, long* ress, const size_t index) {
    // printf("Sono il figlio %d\n", getpid());
    // printf("Parametri: nRows=%zu, startCol=%zu, steps=%zu, index=%zu\n", nRows, startCol, steps, index);

    long sum = 0;

    // passo verticalmente sulle righe
    for (size_t r = 0; r < nRows; ++r) {
        // passo sulle colonne dedicate a quel processo
        for (size_t c = startCol; c < startCol + steps; ++c) {
            sum += matrix[r][c];
        }
    }

    // cella riservata a questo processo
    ress[index] = sum;
    // printf("Somma del processo %zu: %ld\n", index, sum);

    exit(EXIT_SUCCESS);
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

    int** matrix = calloc(rows, sizeof(int*));
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = calloc(cols, sizeof(int));
    }

    readFile(filename, matrix, rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        int* line = matrix[i];
        for (size_t j = 0; j < cols; ++j) {
            printf("%d ", line[j]);
        }
        printf("\n");
    }

    size_t nproc;
    printf("Inserisci il numero dei processi: ");
    scanf("%d", &nproc);


    printf("Numero di processi: %d \n", nproc);

    pid_t* pids = malloc(nproc * sizeof(pid_t));


    int shmid = shmget(IPC_PRIVATE, nproc * sizeof(long), IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("Errore creazione memoria condivisa");
        exit(EXIT_FAILURE);
    }

    long* ress = (long*) shmat(shmid, NULL, 0);

    if (ress == NULL) {
        perror("Errore collegamento memoria condivisa");
        exit(EXIT_FAILURE);
    }

    // rows = 2
    // cols = 5
    // p = 3
    // 5 / 3 = 1
    // 5 % 3 = 2
    // 1 | 1 | (1 + 2)
    int colsxproc = cols / nproc;
    int colsxproc_resto = cols % nproc;

    for (size_t i = 0; i < nproc; ++i) {
        pids[i] = fork();
        printf("pid %d\n", pids[i]);
        
        if(pids[i] < 0){
            
            perror("fork fail");
            exit(EXIT_FAILURE);
        
        } else if(pids[i] == 0){
            
            size_t start_col = i * colsxproc;

            // se è l'ultimo processo, aggiungi il resto
            size_t steps = (i == nproc - 1) ? colsxproc + colsxproc_resto : colsxproc;
            child(matrix, rows, start_col, steps, ress, i);
            
        } else if (pids[i] > 0){
            // prinf("sono il il padre %d\n", getpid());
        }
    }


    bool pidsOk = true;
    for(size_t i = 0; i < nproc; ++i){
        if(pids[i] > 0){
            waitpid(pids[i], NULL, 0);
        } else {
            pidsOk = false;
        }
    }

    if (pidsOk) {
        
        printf("Tutti i processi sono terminati correttamente.\n");
        
        long sum = 0;

        for (size_t i = 0; i < nproc; ++i) {
            sum += ress[i];
        }

        printf("Somma: %ld\n", sum);
    
    } else {

        printf("Almeno un processo non ha terminato correttamente.\n");
    }

    

    for (size_t i = 0; i < rows; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    free(pids);

    // rimuovo la memoria condivisa
    shmdt(ress);
    shmctl(shmid, IPC_RMID, NULL);


    return EXIT_SUCCESS;
}
