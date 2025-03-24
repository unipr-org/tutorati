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
    for(int i = 0; i < N; ++i) {
        pthread_cond_init(&cond[i], NULL);
        state[i] = THINKING;
    }
}

// verifica se un filosofo può mangiare
int
canEat(int philId) {
    return (state[philId] == HUNGRY &&
            state[LEFT(philId)] != EATING &&
            state[RIGHT(philId)] != EATING);
}

void
test(int philId) {
    if (canEat(philId)) {
        state[philId] = EATING;
        pthread_cond_signal(&cond[philId]);
    }
}

void
pickupChopsticks(int philId) {
    pthread_mutex_lock(&mutex);
    
    state[philId] = HUNGRY;
    printf("Il filosofo %d è affamato\n", philId);
    
    
    // verifica se può mangiare
    test(philId);
    
    // se non può mangiare, aspetta
    while (state[philId] != EATING) {
        pthread_cond_wait(&cond[philId], &mutex);
    }
    
    printf("Il filosofo %d sta mangiando\n", philId);
    pthread_mutex_unlock(&mutex);
}

void
returnChopsticks(int philId) {
    pthread_mutex_lock(&mutex);
    
    state[philId] = THINKING;
    printf("Il filosofo %d sta pensando\n", philId);
    
    // verifica se i vicini possono mangiare
    test(LEFT(philId));
    test(RIGHT(philId));
    
    pthread_mutex_unlock(&mutex);
}

void*
philosopher(void* arg) {
    int philId = *(int*)arg;
    
    int run = 1;
    while(run) {
        printf("Il filosofo %d sta pensando\n", philId);
        sleep(rand() % 3);
        
        pickupChopsticks(philId);
        
        sleep(rand() % 3);
        
        returnChopsticks(philId);

        pthread_mutex_lock(&terminationLock);
        if (stop){
            printf("Il filosofo %d sta terminando\n", philId);
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
    
    // Creazione dei thread filosofi
    for(int i = 0; i < N; ++i) {
        philIds[i] = i;
        if(pthread_create(&philosophers[i], NULL, philosopher, &philIds[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    
    printf("\nPremi invio per terminare\n");
    getchar();

    pthread_mutex_lock(&terminationLock);
    printf("*******************************\n");
    printf("Terminazione in corso\n");
    stop = 1;
    printf("*******************************\n");
    pthread_mutex_unlock(&terminationLock);
    
    // Attesa terminazione thread
    for(int i = 0; i < N; ++i) {
        pthread_join(philosophers[i], NULL);
    }
    
    cleanup();
    
    return 0;
}