#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <time.h>

#define NUM_BIN 100
#define POWER 10
#define DATA_MAX 10000000
#define BLOCKSIZE 1024

using namespace std;

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

__global__ void histoKernel(int* data, int* histo, int data_size, int bin_size)
{
    // Calculate global thread ID
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    int bin_idx, i;
    for (i = tid; i < data_size; i += (gridDim.x * blockDim.x))
    {
        bin_idx = (data[i] - 1) / bin_size;        
        atomicAdd(&histo[bin_idx], 1);
    }
}


int main (int argc, char** argv) {
    int histogram[NUM_BIN];
    double start, finish, total;
    int N = pow(2, POWER);
    printf("Number of datapoints: %d (2^%d), number of bins: %d \n", N, POWER, NUM_BIN);
    
    int data[N];
    int *device_data, *device_histo;

    init_histo(histogram);
    create_rand(data, N);

    size_t input_size = N*sizeof(int);
    size_t output_size = NUM_BIN*sizeof(int);

    // allocate GPU memory
    cudaMalloc(&device_data, input_size);
    cudaMalloc(&device_histo, output_size);

    int grid_dim = ceil(N/(float)BLOCKSIZE);
    dim3 threadPerBlock(BLOCKSIZE, 1, 1);
    dim3 blockPerGrid(grid_dim, 1, 1);
    int bin_size = DATA_MAX / NUM_BIN;
    printf("block size: %d, grid size: %d\n", BLOCKSIZE, grid_dim);

    start = CLOCK();

    // copy data
    cudaMemcpy(device_data, data, input_size, cudaMemcpyHostToDevice);
    cudaMemcpy(device_histo, histogram, output_size, cudaMemcpyHostToDevice);    

    // kernel launch
    histoKernel<<<blockPerGrid, threadPerBlock>>>(device_data, device_histo, N, bin_size);
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));

    cudaMemcpy(histogram, device_histo, output_size, cudaMemcpyDeviceToHost);

    finish = CLOCK();
    total = finish - start;
    printf("The total time for histogram generation = %f ms\n", total);

    // Write the data out
    ofstream output_file;
    output_file.open("histogram.dat", ios::out | ios::trunc);
    for(int i = 0; i < NUM_BIN; i++){
        output_file << histogram[i] << " \n";
    }
    output_file.close();

    // Release device memory
    cudaFree(device_data);
    cudaFree(device_histo);

    return 0;
}