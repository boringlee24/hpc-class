#include <omp.h>
#include <stdio.h>
#define N 1000

int  main(int argc, char *argv[]) {
 
 int i, chunk;
 float a[N], b[N], c;
 int thread_id;

 
 /* Some initializations */


 c = 0;
 for (i=0; i < N; i++)
   {
    a[i] = 1.0;
    b[i] = 1.0;
   }

// The chunk size tells OpenMP to give each thread a set number of loop iterations
// The nowait clause avoids the implicit barrier at the end of the parallel region
#pragma omp parallel private(thread_id) reduction(+:c)
 {
#pragma omp for schedule(static,125) 
  for (i=0; i < N; i++)
     c += a[i] + b[i];
   thread_id = omp_get_thread_num();
   printf("Thread %d reports that c = %f\n", thread_id, c);
 }
  /* end of parallel region */
   printf("c = %f\n", c);
return 0;
}

