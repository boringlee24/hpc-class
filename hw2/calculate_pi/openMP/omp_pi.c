#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

double CLOCK() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,  &t);
    return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

// typedef struct 
//  {
//    int in; // number of darts inside circle
//    int out; // number of darts outside circle
//  } PI_DATA;

int throws_per_thread;
// PI_DATA result;

void main(int argc, const char * argv[])
{
    int num_darts = 1000;
    int num_thread = 8;
    int i;
    int in = 0;
    int out = 0;
    double start, finish, total;
    int thread_id;

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

    start = CLOCK();

#pragma omp parallel private(thread_id) reduction(+:in,out)
    {
#pragma omp for schedule(static,throws_per_thread)         
    for (i=0; i < num_darts; i++)
    {
        float x, y;
        float distance;
        x = (float) (rand_r(&thread_id) * 2 - RAND_MAX) / RAND_MAX;
        y = (float) (rand_r(&thread_id) * 2 - RAND_MAX) / RAND_MAX;            
        distance = (float) sqrt(pow(x,2) + pow(y,2));
                if (distance <= 1)
        {
            in += 1;
        }
        else
        {
            out += 1;
        }     
    }
    }

    finish = CLOCK();
    total = finish - start;

    printf("# inside circle: %d, total: %d\n",in, in+out);
    float pi_est = (float) in / (in + out) * 4;
    printf("Estimated PI is %f\n", pi_est);
    printf("Time for calculation: %4.2f milliseconds\n", total);

}


