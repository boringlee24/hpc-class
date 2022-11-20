#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 64
#define BLOCKSIZE 8

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

__global__ void stencil(float* a, float* b)
{
    // Get our global thread ID
    int idx = blockIdx.x*blockDim.x+threadIdx.x;
    int idy = blockIdx.y*blockDim.y+threadIdx.y;
    int idz = blockIdx.z*blockDim.z+threadIdx.z;    

    // load into shared memory then sync threads
    __shared__ float temp[BLOCKSIZE][BLOCKSIZE][BLOCKSIZE];
    temp[threadIdx.x][threadIdx.y][threadIdx.z] = b[idx+N*(idy+N*idz)];
    __syncthreads();

    // use temp to calculate a
    if ((idx >= 1) && (idx < N-1) && (idy >= 1) && (idy < N-1) && (idz >= 1) && (idz < N-1))
    {
        float x_part = (threadIdx.x >= 1 ? temp[threadIdx.x-1][threadIdx.y][threadIdx.z] : b[(idx-1)+N*(idy+N*idz)]) + 
                        (threadIdx.x < BLOCKSIZE-1 ? temp[threadIdx.x+1][threadIdx.y][threadIdx.z] : b[(idx+1)+N*(idy+N*idz)]);
        float y_part = (threadIdx.y >= 1 ? temp[threadIdx.x][threadIdx.y-1][threadIdx.z] : b[idx+N*((idy-1)+N*idz)]) + 
                        (threadIdx.y < BLOCKSIZE-1 ? temp[threadIdx.x][threadIdx.y+1][threadIdx.z] : b[idx+N*((idy+1)+N*idz)]);
        float z_part = (threadIdx.z >= 1 ? temp[threadIdx.x][threadIdx.y][threadIdx.z-1] : b[idx+N*(idy+N*(idz-1))]) + 
                        (threadIdx.z < BLOCKSIZE-1 ? temp[threadIdx.x][threadIdx.y][threadIdx.z+1] : b[idx+N*(idy+N*(idz+1))]);                            
        a[idx+N*(idy+N*idz)] = 0.8 * (x_part + y_part + z_part);
    }
    else
    {
        a[idx+N*(idy+N*idz)] = 0;
    }
}


int main (int argc, char** argv) {
    float a[N][N][N], b[N][N][N];
    double start, finish, total;
    
    printf("input dimension: %dx%dx%d\n", N, N, N);
    
    float *device_a, *device_b;
    int i, j, k;

    /* initialize a dense matrix */
    for(i=0; i<N; i++){    
        for(j=0; j<N; j++){
            for(k=0; k<N; k++){
                b[i][j][k] = 1.25; //then a[][][] = 6
            }
        }
    }

    size_t size = N*N*N*sizeof(float);

    // allocate GPU memory
    cudaMalloc(&device_a, size);
    cudaMalloc(&device_b, size);

    int grid_dim = ceil(N/(float)BLOCKSIZE);
    dim3 threadPerBlock(BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
    dim3 blockPerGrid(grid_dim, grid_dim, grid_dim);
    printf("block size: %d^3, grid size: %d^3\n", BLOCKSIZE, grid_dim);


    // copy data
    // cudaMemcpy(device_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, b, size, cudaMemcpyHostToDevice);    

    // kernel launch
    start = CLOCK();
    stencil<<<blockPerGrid, threadPerBlock>>>(device_a, device_b);
    finish = CLOCK();

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));

    cudaMemcpy(a, device_a, size, cudaMemcpyDeviceToHost);

    total = finish - start;
    printf("The total time for stencil operation = %4.4f ms\n", total);

    printf("a[1][2][%d] = %f, a[8][8][8] = %f\n", N-1, a[1][2][N-1], a[8][8][8]);
    printf("expected values: 0 and 6\n");

    // Release device memory
    cudaFree(device_a);
    cudaFree(device_b);

    return 0;
}