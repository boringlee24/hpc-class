#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main() {
    int i;
    int n = 1000000;
    double start, finish, total;
    double sum = 0;
    double *h_a;
    double *h_b;
    double *h_c;
    size_t bytes = n*sizeof(double);

    h_a = (double*)malloc(bytes);
    h_b = (double*)malloc(bytes);
    h_c = (double*)malloc(bytes);

for( i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
    }

for( i = 0; i < n; i++ ) {
        h_c[i] = h_a[i] + h_b[i];
    }

/* Start timing */
   start = CLOCK();

for(i=0; i<n; i++)
       sum += h_c[i];
finish = CLOCK(); 
printf("final result: %f\n", sum/n);
/* End timing */
total = finish - start;
printf("Time for the loop = %4.2f milliseconds\n", total);
return 0;
}

