#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#define M 500 

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

main(int argc, char **argv)
{
    int i,j,k,jj,kk,en;
    double start, finish, total1, total2, total3, sum;
    int a[M][M], b[M][M], c[M][M];

    srand(145);
    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          a[i][j] = (float)rand()/(float)RAND_MAX;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           b[i][j] = (float)rand()/(float)RAND_MAX;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0;

    start = CLOCK();
    for (i=0; i<M; i++)
      for (j=0; j<M; j++)
         b[i][j] = a[i][j];

    for (i=0; i<M; i++)
      for (j=0; j<M; j++)
         c[i][j] = a[i][j];
   
    finish = CLOCK();
    total1 = finish - start;
    printf("Time for the loop = %f\n", total1);

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0;

    start = CLOCK();
    for (i=0; i<M; i++)
      for (j=0; j<M; j++) {
	 b[i][j] = a[i][j];
         c[i][j] = a[i][j];
        }
   
    finish = CLOCK();
    total2 = finish - start;
    printf("Time for the loop = %f\n", total2);
    return 0;
}

