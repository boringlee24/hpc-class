#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 512        
#define BLOCKSIZE 32
#define GRIDSIZE 16

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}
 
// CUDA kernel. Each thread takes care of one element of c
__global__ void matmulKernel(double *a, double *b, double *c, int n, int grid_size)
{
    // Get our global thread ID
    int idx = blockIdx.x*blockDim.x+threadIdx.x;
    int idy = blockIdx.y*blockDim.y+threadIdx.y;
 
    // Make sure we do not go out of bounds
    if ((idx < n) && (idy < n))
    {
        int num_repeat = GRIDSIZE / grid_size;
        int i, j, k;
        for (i=0; i<num_repeat; i++)
        {
            for (j=0; j<num_repeat; j++)
            {
                double sum = 0;
                int new_idy = idy + BLOCKSIZE * grid_size * j;
                int new_idx = idx + BLOCKSIZE * grid_size * i;
                for (k=0; k<n; k++)
                {
                    sum += a[new_idy*n+k] * b[k*n+new_idx];
                }
                c[new_idy*n+new_idx] = sum;
            }
        }        
    }        
}
 
int main( int argc, char* argv[] )
{
    double a[N][N]; /* input matrix */
    double b[N][N]; /* input matrix */
    double c[N][N]; /* result matrix */
    double *deviceA, *deviceB, *deviceC;
    int i,j;
    double start, finish, total;
    size_t size = N*N*sizeof(double);
    int n = N;
    int grid_size = GRIDSIZE;

    if (argc == 2)
    {
        grid_size = strtol(argv[1], NULL, 10); 
        printf("Strong scaling test: grid dimension = (%d,%d) \n", grid_size, grid_size);
    }

    /* initialize a dense matrix */
    for(i=0; i<N; i++){    
        for(j=0; j<N; j++){
        a[i][j] = (double)(i+j);
        b[i][j] = (double)(i-j);
        }
    }

    // allocate GPU memory space
    cudaMalloc(&deviceA, size);
    cudaMalloc(&deviceB, size);
    cudaMalloc(&deviceC, size);

    start = CLOCK();

    // copy data
    cudaMemcpy(deviceA, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, b, size, cudaMemcpyHostToDevice);

    dim3 dimBlock(BLOCKSIZE, BLOCKSIZE, 1);
    dim3 dimGrid(grid_size,grid_size,1);

    matmulKernel<<<dimGrid, dimBlock>>>(deviceA, deviceB, deviceC, n, grid_size);
 
    // Copy array back to host
    cudaMemcpy(c, deviceC, size, cudaMemcpyDeviceToHost);
 
    finish = CLOCK();

    printf("A result %g \n", c[7][8]);
    total = finish - start;
    printf("The total time for matrix multiplication with dense matrices = %f ms\n", total);
 
    /************************************************************************/
    // now do the sparse matrix multiply

    /* initialize a sparse matrix */
    int num_zeros = 0; 
    for(i=0; i<N; i++){    
        for(j=0; j<N; j++){
        if ((i<j)&&(i%2>0))
            {
            a[i][j] = (double)(i+j);
            b[i][j] = (double)(i-j);
            }
        else
            { 
            num_zeros++;
            a[i][j] = 0.0;
            b[i][j] = 0.0;
            }        
        }
    }    

    start = CLOCK();

    // copy data
    cudaMemcpy(deviceA, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, b, size, cudaMemcpyHostToDevice);

    matmulKernel<<<dimGrid, dimBlock>>>(deviceA, deviceB, deviceC, n, grid_size);
 
    // Copy array back to host
    cudaMemcpy(c, deviceC, size, cudaMemcpyDeviceToHost);

 
    finish = CLOCK();
    total = finish-start;
    printf("A result %g \n", c[7][8]); /* prevent dead code elimination */
    printf("The total time for matrix multiplication with sparse matrices = %f ms\n", total);
    printf("The sparsity of the a and b matrices = %f \n", (float)num_zeros/(float)(N*N));

    // Release device memory
    cudaFree(deviceA);
    cudaFree(deviceB);
    cudaFree(deviceC);
 
    return 0;
}
