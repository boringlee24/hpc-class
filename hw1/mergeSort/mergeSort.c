#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mergeSort.h"

/* define variables for the problem */

#define CHECK_NUM 10
#define SIZE 30000
#define MAX_NUM 1000000
#define MIN_NUM  1
#define NUM_THREADS 4

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}


int arr[SIZE];

const int OFFSET = SIZE % NUM_THREADS;
const int SIZE_PER_THREAD = SIZE / NUM_THREADS;

int rand_gen(int LB, int UB) {
    return LB + ((double) rand() / RAND_MAX) * (UB - LB);
}

// after all threads are done, merge the arrays
void final_merge(int arr[], int number, int merge_depth) {
    for(int i = 0; i < number; i = i + 2) {

        int left = i * (SIZE_PER_THREAD * merge_depth);
        int right = ((i + 2) * SIZE_PER_THREAD * merge_depth) - 1;
        int middle = left + (SIZE_PER_THREAD * merge_depth) - 1;

        if (right >= SIZE) {
            right = SIZE - 1;
        }

        merge(arr, left, middle, right);
    }
    if (number / 2 >= 1) {
        final_merge(arr, number / 2, merge_depth * 2);
    }
}

void print_first_k(int arr[], int k) {
    printf("Printing first %d elements of array\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// what each thread worker does
void *pthread_worker(void* arg)
{
    int thread_id = (long)arg;
    int left = thread_id * (SIZE_PER_THREAD);
    int right = (thread_id + 1) * (SIZE_PER_THREAD) - 1;
    if (thread_id == NUM_THREADS - 1) {
        right += OFFSET;
    }
    int middle = left + (right - left) / 2;
    if (left < right) {
        sort(arr, left, right);
        sort(arr, left + 1, right);
        merge(arr, left, middle, right);
    }
    return NULL;
}

// iterative perform merge sort
void sort(int arr[], int left, int right) {
    if (left < right) {
        int middle = (right - left) / 2 + left;
        sort(arr, left, middle);
        sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

// merge two sorted chunks
void merge(int arr[], int left, int middle, int right) {
    int i = 0, j = 0, k = 0;    
    int Lsize = middle - left + 1;
    int Rsize = right - middle;
    int left_array[Lsize], right_array[Rsize];    
    
    for (int i = 0; i < Lsize; i ++) {
        left_array[i] = arr[left + i];
    }
    
    for (int j = 0; j < Rsize; j ++) {
        right_array[j] = arr[middle + 1 + j];
    }
    
    i = 0, j = 0;    
    while (i < Lsize && j < Rsize) {
        if (left_array[i] <= right_array[j]) {
            arr[left + k] = left_array[i];
            i ++;
        } else {
            arr[left + k] = right_array[j];
            j ++;
        }
        k ++;
    }
    
    while (i < Lsize) {
        arr[left + k] = left_array[i];
        k ++;
        i ++;
    }
    while (j < Rsize) {
        arr[left + k] = right_array[j];
        k ++;
        j ++;
    }
}

void main(int argc, const char * argv[]) {
    double start, finish, total;
    
    /* initialize array with random numbers */
    for (int i = 0; i < SIZE; i ++) {
        arr[i] = rand_gen(MIN_NUM, MAX_NUM);
    }
    printf("before sorting\n");
    print_first_k(arr, CHECK_NUM);

    /* begin timing */
    pthread_t threads[NUM_THREADS];
    start = CLOCK();
    
    /* create threads */
    for (long i = 0; i < NUM_THREADS; i ++) {
        int rc = pthread_create(&threads[i], NULL, pthread_worker, (void *)i);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    for(long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    final_merge(arr, NUM_THREADS, 1);
    
    /* end timing */
    finish = CLOCK();
    total = finish - start;

    printf("after sorting\n");
    print_first_k(arr, CHECK_NUM); 
    printf("Time for mergesort: %4.2f milliseconds\n", total);
    
    return;
}


