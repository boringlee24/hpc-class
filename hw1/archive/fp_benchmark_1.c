#include <stdio.h>
#include <stdlib.h>

#define LOOP 1000

int main()
{
    float upperbound = 10.0;
	// generate two random numbers within the range
	float a = (float)rand()/(float)(RAND_MAX) * upperbound;
	float b = (float)rand()/(float)(RAND_MAX) * upperbound;	
    
	for (int i=0;i<LOOP;i++)
	{
		float c = a + b;
		float d = a - b;
		double e = c;
	}
    return 0;
}