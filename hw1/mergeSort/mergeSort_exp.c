#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mergeSort.h"

#define CHECK_NUM 10
#define MAX_NUM 1000000
#define MIN_NUM  1
#define NUM_THREADS 1

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

/* define derived values from the variables */


int rand_gen(int LB, int UB) {
    return LB + ((double) rand() / RAND_MAX) * (UB - LB);
}

/* test to ensure that the array is in sorted order */
void print_first_k(int arr[], int k) {
    printf("Printing first %d elements of array\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int NUMBERS_PER_THREAD, OFFSET;
const int ARR_SIZE=10;
int arr[ARR_SIZE];

int main(int argc, const char * argv[]) {
    double start, finish, total;
    int num_thread = 1;
    // ARR_SIZE = 10;
    if (argc > 1){
        num_thread = strtol(argv[1], NULL, 10);        
    }
    printf("Number of threads: %d \n", num_thread);
    if (argc > 2){
        ARR_SIZE = strtol(argv[2], NULL, 10);
    }
	printf("Array size %d \n", ARR_SIZE);

    NUMBERS_PER_THREAD = ARR_SIZE / NUM_THREADS;
    OFFSET = ARR_SIZE % NUM_THREADS;

    for (int i = 0; i < ARR_SIZE; i ++) {
        arr[i] = rand_gen(MIN_NUM, MAX_NUM);
    }
    // // print generated array
    // printf("Printing first %d elements of unsorted array\n", CHECK_NUM);
    // for (int i = 0; i < CHECK_NUM; i++) {
    //     printf("%d ", arr[i]);
    // }
    print_first_k(arr, CHECK_NUM);
    
    /* begin timing */
    pthread_t threads[NUM_THREADS];
    start = CLOCK();
    
    /* create threads */
    for (long i = 0; i < NUM_THREADS; i ++) {
        int rc = pthread_create(&threads[i], NULL, thread_merge_sort, (void *)i);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    for(long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    merge_sections_of_array(arr, NUM_THREADS, 1);
    
    /* end timing */
    finish = CLOCK();
    total = finish - start;

    printf("Time for mergesort: %4.2f milliseconds\n", total);
    /* test to ensure that the array is in sorted order */
    print_first_k(arr, CHECK_NUM); 
    return 0;
}

/* merge locally sorted sections */
void merge_sections_of_array(int arr[], int number, int aggregation) {
    for(int i = 0; i < number; i = i + 2) {
        int left = i * (NUMBERS_PER_THREAD * aggregation);
        int right = ((i + 2) * NUMBERS_PER_THREAD * aggregation) - 1;
        int middle = left + (NUMBERS_PER_THREAD * aggregation) - 1;
        if (right >= ARR_SIZE) {
            right = ARR_SIZE - 1;
        }
        merge(arr, left, middle, right);
    }
    if (number / 2 >= 1) {
        merge_sections_of_array(arr, number / 2, aggregation * 2);
    }
}

/** assigns work to each thread to perform merge sort */
void* thread_merge_sort(void* arg);
{
    int left = thread_id * (NUMBERS_PER_THREAD);
    int right = (thread_id + 1) * (NUMBERS_PER_THREAD) - 1;
    if (thread_id == NUM_THREADS - 1) {
        right += OFFSET;
    }
    int middle = left + (right - left) / 2;
    if (left < right) {
        merge_sort(arr, left, right);
        merge_sort(arr, left + 1, right);
        merge(arr, left, middle, right);
    }
    return NULL;
}

/* perform merge sort */
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

/* merge function */
void merge(int arr[], int left, int middle, int right) {
    int i = 0;
    int j = 0;
    int k = 0;
    int left_length = middle - left + 1;
    int right_length = right - middle;
    int left_array[left_length];
    int right_array[right_length];
    
    /* copy values to left array */
    for (int i = 0; i < left_length; i ++) {
        left_array[i] = arr[left + i];
    }
    
    /* copy values to right array */
    for (int j = 0; j < right_length; j ++) {
        right_array[j] = arr[middle + 1 + j];
    }
    
    i = 0;
    j = 0;
    /** chose from right and left arrays and copy */
    while (i < left_length && j < right_length) {
        if (left_array[i] <= right_array[j]) {
            arr[left + k] = left_array[i];
            i ++;
        } else {
            arr[left + k] = right_array[j];
            j ++;
        }
        k ++;
    }
    
    /* copy the remaining values to the array */
    while (i < left_length) {
        arr[left + k] = left_array[i];
        k ++;
        i ++;
    }
    while (j < right_length) {
        arr[left + k] = right_array[j];
        k ++;
        j ++;
    }
}