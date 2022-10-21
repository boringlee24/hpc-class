#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "clock.h"

#define N 20

double factorial(double n)
{
    if (n == 0)
        return 1;
    else
        return n*factorial(n-1);
}

void main(int argc, const char * argv[])
{
    double sine = 0;
    int i = 0;
    double x = 0;
    if (argc > 1)
    {
        x = (double) atof(argv[1]); 
    }
    printf("Input x = %1.10lf\n", x);

    double start, finish, total;
    start = CLOCK();

    for (i=0;i<N;i++)
    {
        sine += pow(-1, i) / factorial(2*i + 1) * pow(x, (2*i+1));
    }
    finish = CLOCK();
    total = finish - start;

    printf("Output sin(x) = %1.10lf\n", sine);
    printf("Time for calculation: %4.4f milliseconds\n", total);
    
    return;
}
