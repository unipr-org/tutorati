#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define LEFT(i) ((i + N - 1) % N)
#define RIGHT(i) ((i + 1) % N)
enum { THINKING, HUNGRY, EATING } state[N];


// variabile condivisa per terminare i thread
int stop = 0;
pthread_mutex_t terminationLock;


// implementazione del monitor
pthread_mutex_t mutex;
pthread_cond_t cond[N];

// inizializzazione monitor
void
initMonitor() {
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < N; ++i)
        pthread_cond_init(&cond[i], NULL);
}

void
pickupChopsticks(int philId) {
    pthread_mutex_lock(&mutex);
    
    state[philId] = HUNGRY;
    printf("Il filosofo %d è affamato\n", philId);
    
    // il filosofo prende le bacchette senza controllare
    // se sono entrambe libere
    printf("Il filosofo %d sta aspettando le bacchette\n", philId);
    pthread_cond_wait(&cond[philId], &mutex);
    
    state[philId] = EATING;

    printf("Il filosofo %d sta mangiando\n", philId);
    pthread_mutex_unlock(&mutex);
}

void
returnChopsticks(int philId) {
    pthread_mutex_lock(&mutex);
    
    state[philId] = THINKING;
    printf("Il filosofo %d sta pensando\n", philId);
    

    if (state[LEFT(philId)] == HUNGRY) {
        pthread_cond_signal(&cond[LEFT(philId)]);
    }
    if (state[RIGHT(philId)] == HUNGRY) {
        pthread_cond_signal(&cond[RIGHT(philId)]);
    }
    
    pthread_mutex_unlock(&mutex);
}

void*
philosopher(void* arg) {
    int philId = *(int*)arg;
    
    int run = 1;
    while(run) {
        printf("Il filosofo %d sta pensando\n", philId);
        sleep(rand() % 2);
        
        pickupChopsticks(philId);
        
        // sleep(rand() % 2);
        
        returnChopsticks(philId);

        pthread_mutex_lock(&terminationLock);
        if (stop){
            printf("Uno scrittore sta terminando\n");
            run = 0;
        }
        pthread_mutex_unlock(&terminationLock);
    }
    pthread_exit(NULL);
}

void
cleanup() {
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&terminationLock);
    for(int i = 0; i < N; ++i) {
        pthread_cond_destroy(&cond[i]);
    }
}


int
main() {
    
    pthread_t philosophers[N];
    int philIds[N];
    pthread_mutex_init(&terminationLock, NULL);
    
    initMonitor();
    

    for(int i = 0; i < N; ++i) {
        philIds[i] = i;

        if(pthread_create(&philosophers[i], NULL, philosopher, &philIds[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    
    printf("\nPremi qualsiasi tasto per terminare\n");
    getchar();

    pthread_mutex_lock(&terminationLock);
    printf("*******************************");
    printf("Terminazione in corso\n");
    stop = 1;
    printf("*******************************");
    pthread_mutex_unlock(&terminationLock);

    for(int i = 0; i < N; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    cleanup();
    return 0;
}