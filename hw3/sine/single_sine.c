#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "clock.h"

#define N 20

float factorial(float n)
{
    if (n == 0)
        return 1;
    else
        return n*factorial(n-1);
}

void main(int argc, const char * argv[])
{
    float sine = 0;
    int i = 0;
    float x = 0;
    if (argc > 1)
    {
        x = (float) atof(argv[1]); 
    }
    printf("Input x = %1.10f\n", x);

    double start, finish, total;
    start = CLOCK();
    for (i=0;i<N;i++)
    {
        sine += powf(-1, i) / factorial(2*i + 1) * powf(x, (2*i+1));
    }
    finish = CLOCK();
    total = finish - start;

    printf("Output sin(x) = %1.10f\n", sine);
    printf("Time for calculation: %4.4f milliseconds\n", total);

    return;
}
