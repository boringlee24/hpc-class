#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Use N number of semaphores, each corresponding to a fork

// To avoid deadlock, force the starting direction for the first 
// N-1 people to go right -> left, and force the last person to
// go from left -> right

double CLOCK() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,  &t);
    return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

typedef struct 
 {
   int in; // number of darts inside circle
   int out; // number of darts outside circle
 } PI_DATA;

typedef struct
{
   int	thread_id;
   int  num_throws;   
} THREAD_DATA;

int throws_per_thread;
sem_t sema;
PI_DATA result;

void* thread_routine(void* args){
    THREAD_DATA *thread_input;
    thread_input = (THREAD_DATA *) args;
    int num_throws = thread_input->num_throws;
    int thread_id = thread_input->thread_id;
    // printf("number of throws %d, thread %d \n", num_throws, thread_id);
    int i;
    int in = 0;
    int out = 0;
    float x, y;
    float distance;
    
    for(i=0; i<num_throws; i++) {        
        // generate random x and y value between -1 and 1        
        x = (float) (rand_r(&thread_id) * 2 - RAND_MAX) / RAND_MAX;
        y = (float) (rand_r(&thread_id) * 2 - RAND_MAX) / RAND_MAX;            
        distance = (float) sqrt(pow(x,2) + pow(y,2));
        // printf("x: %f, y: %f, distance: %f \n", x, y, distance);
        if (distance <= 1)
        {
            in += 1;
        }
        else
        {
            out += 1;
        }          
    }
    // printf("in: %d, out: %d\n", in, out);
    // update global variable
    sem_wait(&sema);
    result.in += in;
    result.out += out;
    sem_post(&sema);      
}

void main(int argc, const char * argv[])
{
    int num_darts = 1000;
    int num_thread = 8;
    int i;
    result.in = 0;
    result.out = 0;
    double start, finish, total;

    if (argc > 1)
    {
        num_thread = strtol(argv[1], NULL, 10); 
    }
    printf("Number of threads: %d \n", num_thread);
    if (argc > 2){
        num_darts = strtol(argv[2], NULL, 10);
    }
	printf("Number of darts %d \n", num_darts);

    throws_per_thread = num_darts / num_thread;
	printf("Number of darts per thread %d \n", throws_per_thread);

    pthread_t tid[num_thread];    
    THREAD_DATA td_array[num_thread];
    sem_init(&sema, 0, 1);

    start = CLOCK();

    for(i=0; i<num_thread; i++){
        td_array[i].thread_id = i;
        td_array[i].num_throws = throws_per_thread;
        pthread_create(&tid[i], NULL, thread_routine, (void *)&td_array[i]);
    }

    // join thread
    for(i=0; i<num_thread; i++){
        pthread_join(tid[i], NULL);
    }

    finish = CLOCK();
    total = finish - start;

    sem_destroy(&sema);

    printf("# inside circle: %f, total: %f\n",result.in, result.in+result.out);
    float pi_est = (float) result.in / (result.in + result.out) * 4;
    printf("Estimated PI is %f\n", pi_est);
    printf("Time for calculation: %4.2f milliseconds\n", total);

    return;
}