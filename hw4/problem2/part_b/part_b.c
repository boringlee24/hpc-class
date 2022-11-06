#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BIN 20
#define NUM_DATA 2000000
#define DATA_MAX 1000000
// #define BIN_SIZE DATA_MAX / NUM_BIN

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

void create_rand(int* histogram, int size, int seed) {
	srand(seed);
	int rand_gen, bin_index;
	int bin_size = DATA_MAX / NUM_BIN;
	int i;
	for (i = 0; i < size; i++)
	{
		rand_gen = rand() % DATA_MAX + 1;
		// figure out which bin it falls into
		bin_index = (rand_gen - 1) / bin_size;
		histogram[bin_index] += 1;
	}
}

int main (int argc, char** argv) {
int world_rank;
int world_size;
const int LEAD_RANK = 0;
int num_data_per_proc = NUM_DATA / NUM_BIN;
int histogram[NUM_BIN];
double start, finish, reduce, total;

// int rand_arr[num_data_per_proc];

MPI_Init(NULL, NULL);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

if (world_size != NUM_BIN) {
	fprintf(stderr, "World size must be %d\n", NUM_BIN);
  	MPI_Abort(MPI_COMM_WORLD, 1);
   }

if (world_rank == 0) {
	printf("Number of data per process: %d\n", num_data_per_proc);
	start = CLOCK();
}

// now generate the random data

init_histo(histogram);
create_rand(histogram, num_data_per_proc, world_rank);

// now perform reduce
int global_histogram[NUM_BIN];
MPI_Reduce(&histogram, &global_histogram, NUM_BIN, MPI_INT, MPI_SUM, 0,
			MPI_COMM_WORLD);

// print
if (world_rank == 0) {
	finish = CLOCK();	
	total = finish-start;

	int i;
	for (i = 0; i < NUM_BIN; i++)
	{
		printf("Number of elements in bin %d: %d\n", i, global_histogram[i]);
	}	
	printf("The total time for histogram generation = %f ms\n", total);
}

MPI_Finalize();

}
