/*=================================================================================
 # gcd.c

 #  Copyright (c) 2018 ASCS Laboratory (ASCS Lab/ECE/BU)
 #  Permission is hereby granted, free of charge, to any person obtaining a copy
 #  of this software and associated documentation files (the "Software"), to deal
 #  in the Software without restriction, including without limitation the rights
 #  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 #  copies of the Software, and to permit persons to whom the Software is
 #  furnished to do so, subject to the following conditions:
 #  The above copyright notice and this permission notice shall be included in
 #  all copies or substantial portions of the Software.

 #  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 #  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 #  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 #  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 #  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 #  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 #  THE SOFTWARE.
 ==================================================================================*/
#include <stdio.h> 
#include<stdlib.h>
#include <time.h>

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int product ( int a, int b ) {
  int c = 0;
  if (b != 0)
  {
	  for (int i = 0; i < b; i++)
	  {
		  c = c + a;
	  }
  }
  
  return c;
}

 int main(void)
 {
    int n1, n2, answer;
    double start, finish, total;
    n1 = 500000000;
    n2 = 100000000;
    start = CLOCK();

	  if (n2 < 0)
		  answer = -product(n1, -n2);
	  else
		  answer = product(n1, n2);
    finish = CLOCK();
    total = finish - start;
    printf("Time for Prod = %4.2f milliseconds\n", total);

    return answer;
 }
