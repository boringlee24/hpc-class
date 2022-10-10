#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>

// Use N number of semaphores, each corresponding to a fork

// To avoid deadlock, force the starting direction for the first 
// N-1 people to go right -> left, and force the last person to
// go from left -> right

#define N 5
#define EAT_MAX 2
#define THINK_MAX 4
#define ITER 12

sem_t forks[N]; 

void* eater_routine(void* args){
    int num = *(int *)args;
    int i;
    for(i=0; i<ITER; i++) {
        // think for a random amount of time
        printf("Philosopher %d is thinking\n", num);
        sleep(rand() % (THINK_MAX) + 1);

        // now try to eat
        printf("Philosopher %d is trying to eat\n", num);

        // left first for last eater, right first for other eaters
        // to prevent deadlock
        if (num == N-1) {
            sem_wait(&forks[(num+1) % N]);
            printf("Philosopher %d takes fork %d\n", num, (num+1) % N);            
            sem_wait(&forks[(num) % N]);
            printf("Philosopher %d takes fork %d\n", num, (num) % N);
        }
        else {
            sem_wait(&forks[(num) % N]);
            printf("Philosopher %d takes fork %d\n", num, (num) % N);
            sem_wait(&forks[(num+1) % N]);                        
            printf("Philosopher %d takes fork %d\n", num, (num+1) % N);            
        }

        // now eat
        printf("Philosopher %d is eating\n", num);
        sleep(rand() % (EAT_MAX) + 1);

        // release forks
        sem_post(&forks[(num) % N]);
        printf("Philosopher %d releases fork %d\n", num, (num) % N);
        sem_post(&forks[(num+1) % N]);                        
        printf("Philosopher %d releases fork %d\n", num, (num+1) % N);                    
    }
    printf("Philosopher %d has left the game\n", num);
}

void main()
{
    pthread_t tid[N];
    int eater[N], i;

    for(i=0; i<N; i++){
        sem_init(&forks[i], 0, 1); //shared by threads, init to 1 (fork available)
        printf("fork %d is available\n", i);
    }

    for(i=0; i<N; i++){
        eater[i] = i;
        pthread_create(&tid[i], NULL, eater_routine, (void *)&eater[i]);
    }

    // join thread
    for(i=0; i<N; i++){
        pthread_join(tid[i], NULL);
    }

    for(i=0; i<N; i++){
        sem_destroy(&forks[i]);
    }
    return;
}