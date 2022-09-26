#include <stdlib.h>
#include <stdio.h>
#define NTHREADS 10 
int sum=0;
pthread_mutex_t lock;
pthread_t threads[NTHREADS];

void adder() 
{
 int t;
 pthread_mutex_lock(&lock);
 t = sum;
 sleep(2);
 sum = t+1; 
 printf("sum computed: %d\n", sum);
 pthread_mutex_unlock(&lock);
 return;   
}

int main()
{
 int i;
 if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }

 printf("forking\n");
 for (i=0; i < NTHREADS; i++)
    pthread_create(&threads[i], NULL, &adder, NULL);
 printf("join\n");

 for (i=0; i < NTHREADS; i++)
  pthread_join(threads[i],NULL);
 pthread_mutex_destroy(&lock);
 printf("The final sum computed: %d\n", sum);
 return(0);
}
