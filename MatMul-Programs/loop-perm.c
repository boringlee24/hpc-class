#include <stdio.h>
#include<stdlib.h>
#include <time.h>

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

#define M 128
main(int argc, char **argv)
{
    int i,j,k;
    double start, finish, total1, total2, sum;
    int a[M][M], b[M][M], c[M][M];

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          a[i][j] = 1;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           b[i][j] = 2;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0;

      start = CLOCK();
         for (j=0; j<M; j++)
           for (i=0; i<M; i++)
            for (k = 0; k<M; k++) {
                  c[i][j] = c[i][j] + a[i][k] * b[k][j];
               }
    finish = CLOCK();
    total1 = finish - start;
    printf("Time for the loop = %f\n", total1); 
    printf("The sum is: %ld\n", c[99][99]);

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0;

      start = CLOCK();
      for (i=0; i<M; i++)
         for (j=0; j<M; j++)
            for (k = 0; k<M; k++) {
                  c[i][j] = c[i][j] + a[i][k] * b[k][j];
               }
    finish = CLOCK();
    total2 = finish - start;
    printf("Time for the loop = %f\n", total2); 
    printf("The sum is: %ld\n", c[99][99]);

    return 0;
}
