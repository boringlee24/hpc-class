# How to run the dining philosopher code

Go into `pthread_semaphore.c` and find the line

```
#define N 5
```

Modify the value of "N" depending on the number of philosophers.

Next, do 
```
make target
make run
```

The program will print the status of a philosopher whenever it changes. The three statuses are: **is thinking**, **tries to eat**, and **is eating**.

The program will also print the status of each fork whenever it is taken or released by a philosopher. The statuses are: **Philosopher X takes fork Y** and **Philosopher X releases fork Y**.