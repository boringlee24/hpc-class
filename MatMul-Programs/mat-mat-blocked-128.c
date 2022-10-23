#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#define M 512 
#define B 128 

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
    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          for (k=0; k<M; k++)
           c[i][j] = c[i][j] + a[i][k] * b[k][j];   

    finish = CLOCK();
    total1 = finish - start;
    printf("Check c[511][511] = %li\n", c[511][511]);    



   for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0; 
    
    start = CLOCK();
   
    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          for (k=0; k<M; k++)
           c[i][j] = c[i][j] + a[i][k] * b[k][j];   

    finish = CLOCK();
    total2 = finish - start;
    printf("Check c[511][511] = %li\n", c[511][511]);    
    
   for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0.0; 
    
    en = B * 4;
    start = CLOCK();
   
    for (kk=0; kk<en; kk+=B) 
      for (jj=0; jj<en; jj+=B)      
         for (i=0; i< M; i++)     
            for (j = jj; j< jj + B; j++) {
               sum = c[i][j];
               for (k=kk; k< kk + B; k++) {
//                  printf("i = %li, j = %li; k = %li\n", i, j, k);
                  sum+= a[i][k] * b[k][j];
                  }
                 c[i][j] = sum;
               }

    finish = CLOCK();
    total3 = finish - start;
   
    printf("Check c[511][511] = %li\n", c[511][511]);    
    
    printf("Time for first loop = %f\n", total1);
    printf("Time for second loop = %f\n", total2);
    printf("Time for third loop = %f\n", total3);
  
    return 0;
}
