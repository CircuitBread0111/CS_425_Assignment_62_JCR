///////////////////////////|
//|File: pth_addition.c
//|Author: Jerrin C. Redmon
//|Language: C
//|Version: 1.0.0
//|Date: April 14, 2025
///////////////////////////|

/* Descriptiion:
* This program demonstrates the use of pthreads to create multiple threads
* that compute the sum of an array. The program takes the number of threads
* as a command line argument. Each thread computes the sum of a portion of
* the array, and the main thread combines the results to get the total sum.
* The program also measures the time taken to compute the sum using multiple
* threads and compares it with the expected sum using Euler's formula.
* The expected sum is calculated using the formula n(n+1)/2, where n is the
* size of the array.
*/

//----------------------------------------------------------------

// Includes //
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#define MAIN_ARRAY 1000000

// Structure to hold thread data //
typedef struct {
    int *array;
    int start;
    int end;
    long long partial_sum;
} ThreadData;

// Sum Array //
void* sum_array(void* arg) {
    ThreadData* data = (ThreadData*)arg;    // Cast the argument to ThreadData
    data->partial_sum = 0;          // Initialize the partial sum
    for (int i = data->start; i < data->end; i++) {
        data->partial_sum += data->array[i];    // Compute the sum of the array segment
    }
    return NULL;
}

// Main //
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);  // Print usage message
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) { // Check if the number of threads is valid
        fprintf(stderr, "Number of threads must be positive.\n");
        return 1;
    }

    int *array = malloc(sizeof(int) * MAIN_ARRAY);  // Allocate memory for the array
    pthread_t* threads = malloc(sizeof(pthread_t) * num_threads);   // Allocate memory for thread IDs
    ThreadData* thread_data = malloc(sizeof(ThreadData) * num_threads); // Allocate memory for thread data

    for (int i = 0; i < MAIN_ARRAY; i++) {
        array[i] = i + 1;
    }

    struct timespec start_time, end_time;       // Variables to hold start and end time
    clock_gettime(CLOCK_MONOTONIC, &start_time);        // Get the start time

    int base_chunk = MAIN_ARRAY / num_threads;  // Calculate the base chunk size
    int remainder = MAIN_ARRAY % num_threads;  // Calculate the remainder
    int offset = 0;                             // Initialize the offset

    for (int i = 0; i < num_threads; i++) {
        int chunk = base_chunk + (i < remainder ? 1 : 0);   // Adjust chunk size for remainder
        thread_data[i] = (ThreadData){array, offset, offset + chunk, 0};    // Initialize thread data
        pthread_create(&threads[i], NULL, sum_array, &thread_data[i]);  // Create thread
        offset += chunk;    //  Update offset for next thread
    }

    long long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL); //  Wait for each thread to finish
        total_sum += thread_data[i].partial_sum;    // Combine partial sums
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);  // Get the end time
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    long long euler_sum = ((long long)MAIN_ARRAY * (MAIN_ARRAY + 1)) / 2;
    printf("Computed sum: %lld\n", total_sum);
    printf("Euler's Formula: %lld\n", euler_sum);
    printf("Wall time with %d threads: %f seconds\n", num_threads, elapsed);

    free(array);        // Free the allocated memory for the array
    free(threads);      // Free the allocated memory for thread IDs
    free(thread_data);  // Free the allocated memory for thread data
    return 0;
}
