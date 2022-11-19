#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_BIN 20
#define POWER 20
#define DATA_MAX 10000000
#define NUM_THREAD 8

double CLOCK() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,  &t);
    return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

void init_histo(int* histogram) {
	int i;
	for (i = 0; i < NUM_BIN; i++)
	{
		histogram[i] = 0;
	}
}

void create_rand(int* data, int N) {
    int rand_gen, i;
	for (i = 0; i < N; i++)
	{
		rand_gen = rand() % DATA_MAX + 1;		
        data[i] = rand_gen;
	}
}
// typedef struct 
//  {
//    int in; // number of darts inside circle
//    int out; // number of darts outside circle
//  } PI_DATA;

int data_per_thread;
// PI_DATA result;

int main(int argc, const char * argv[])
{
    int N = pow(2, POWER);
    int i;
    int histogram[NUM_BIN];    
    double start, finish, total;
    int thread_id;    
    int data[N];
    int bin_size = DATA_MAX / NUM_BIN;

    init_histo(histogram);
    create_rand(data, N);

    data_per_thread = N / NUM_THREAD;
    printf("Number of datapoints: %d (2^%d), number of bins: %d \n", N, POWER, NUM_BIN);
	printf("Number of datapoints per thread %d \n", data_per_thread);

    start = CLOCK();

#pragma omp parallel private(thread_id) reduction(+:histogram)
    {
#pragma omp for schedule(static,data_per_thread)         
    for (i=0; i < N; i++)
    {        
        int bin_idx = (data[i] - 1) / bin_size;
        histogram[bin_idx] += 1;
    }
    }

    finish = CLOCK();
    total = finish - start;
    for (i=0; i<NUM_BIN; i++)
    {
        printf("%d\n", histogram[i]);
    }
    printf("The total time for histogram generation = %4.4f ms\n", total);


    return 0;

}


