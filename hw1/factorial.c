/*=================================================================================
 # factorial.c
 
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

//#include<stdio.h>
#include <stdio.h> 
#include<stdlib.h>
#include <time.h>

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

unsigned int product(unsigned int a, unsigned int b)
{
    unsigned int c = 0;    
    for(int i = 0; i < b; i++)
          c += a;
    return c;
}

unsigned int factorial(unsigned int a)
 {
   if (a == 0)
      return 0;
   if (a == 1)
      return 1;
   else
    {
      a = product(a, factorial(a-1));
      return a;
   }
 }

 int main(void)
 {
    int n, result;
    double start, finish, total;
    n = 14;
    start = CLOCK();
    result = factorial(n);
    finish = CLOCK();
    total = finish - start;
    printf("Time for Facto = %4.2f milliseconds\n", total);
    return result;
 }
