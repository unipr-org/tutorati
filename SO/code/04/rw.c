#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>


// semaforo condiviso tra lettori e scrittori
sem_t rwSem;

// semaforo per l'aggiornamento di readerCount
sem_t countSem;

pthread_t tid;

// processi che attualmente stanno leggendo
size_t readerCount = 0;


// variabile condivisa per terminare i thread
int stop = 0;
pthread_mutex_t terminationLock;


// dati condivisi per la sezione critica
int sharedData = 0;



void
*reader(void* param) {

    int run = 1;

    while(run) {

        // sleep(rand() % 3);

        sem_wait(&countSem);
        ++readerCount;
        
        if (readerCount == 1)
            sem_wait(&rwSem);

        
        sem_post(&countSem);

        // inizio sezione critica in lettura

        printf("\nUn lettore è entrato nella sezione critica\n");
        
        printf("\nDato condiviso: %d\n", sharedData);

        // sleep(rand() % 3);


        // fine sezione critica in lettura

        sem_wait(&countSem);

        --readerCount;
        if (readerCount == 0)
            sem_post(&rwSem);
        
        sem_post(&countSem);


        pthread_mutex_lock(&terminationLock);
        if (stop) {
            printf("\nUn lettore sta terminando\n");
            run = 0;
        }
        pthread_mutex_unlock(&terminationLock);
    }

    pthread_exit(NULL);
}

void
*writer(void* param) {

    int run = 1;
    while(run) {
        printf("Uno scrittore sta cercando di scrivere\n");
        sem_wait(&rwSem);
    
        printf("\nUno scrittore è entrato\n");
        
        // genera un numero randomico
        sharedData = rand() % 100;
        printf("> Uno scrittore ha scritto un dato condiviso\n");

        sem_post(&rwSem);
        printf("Uno scrittore sta uscendo\n");

        pthread_mutex_lock(&terminationLock);
        if (stop){
            printf("Uno scrittore sta terminando\n");
            run = 0;
        }
        pthread_mutex_unlock(&terminationLock);
    }

    pthread_exit(NULL);
}

int
main() {
    
    srand(time(NULL));

    if (pthread_mutex_init(&terminationLock, NULL) != 0) { 
        printf("\nLa creazione del lock non è riuscita\n"); 
        return 1; 
    } 

    if (sem_init(&rwSem,0,1) != 0) {
        printf("\nLa creazione del semaforo non è riuscita\n"); 
        return 1; 
    }


    if (sem_init(&countSem,0,1) != 0) {
        printf("\nLa creazione del semaforo non è riuscita\n"); 
        return 1; 
    }

    size_t nReaders = 2;
    size_t nWriter = 1;
    pthread_t readers[nReaders];
    pthread_t writers[nWriter];

    // creazione dei lettori
    for (size_t i = 0; i < nReaders; ++i) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    // creazione degli scrittori
    for (size_t i = 0; i < nWriter; ++i) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    printf("\nPremi qualsiasi tasto per terminare\n");
    getchar();

    pthread_mutex_lock(&terminationLock);
    printf("*******************************");
    printf("Terminazione in corso\n");
    stop = 1;
    printf("*******************************");
    pthread_mutex_unlock(&terminationLock);

    // attesa della terminazione
    for (size_t i = 0; i < nReaders; ++i) {
        pthread_join(readers[i], NULL);
    }
    for (size_t i = 0; i < nWriter; ++i) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&terminationLock);
    sem_destroy(&rwSem);
    sem_destroy(&countSem);


    return 0;
}