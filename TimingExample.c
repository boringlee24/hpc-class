#include <stdio.h> 
#include<stdlib.h>
#include <time.h>
#define M 256 

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main(int argc, char **argv)
{
    int i,j,k,jj,kk,en;
    double start, finish, total, sum;
    float a[M][M], b[M][M], c[M][M];

/* Set the seed for the random number generators for the data */
    srand(145);

/* Initialize a, b and c */
    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          a[i][j] = (float)rand()/(float)RAND_MAX;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           b[i][j] = (float)rand()/(float)RAND_MAX;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0.;


/* Start timing */
    start = CLOCK();

/* This is the portion of the code you will time to evaluate performance. */

     for (i =0; i<M; i++)
       for (j=0; j<M; j++)
         for (k=0; k<M; k++)
            c[i][j] += a[i][k] * b[k][j];
    finish = CLOCK();
/* End timing */
    total = finish - start;
    printf("Time for the loop = %4.2f milliseconds\n", total);
    return 0;
}

