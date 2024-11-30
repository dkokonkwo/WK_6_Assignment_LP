#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBER 2000
#define MIN_NUMBER 200
#define MAX_SIZE 100

/**
 * struct threadData - structure for thread data
 * @start: starting number
 * @end: ending number
 * @result: sum
 */
typedef struct ThreadData
{
    unsigned long start;
    unsigned long end;
    unsigned long result;
} ThreadData;

/**
 * sum_range - sums the numbes of a given range
 * @arg: function argument
 * Return: void pointer
 */
void *sum_range(void *arg)
{
    unsigned long i;
    ThreadData* data = (ThreadData *)arg;
    data->result = 0;

    for (i = data->start; i <= data->end; i++)
        data->result += i;

    return NULL;
}

/**
 * main - calculates the sum of n numbers usins multiple threads
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
    unsigned long n, start, total_sum = 0;
    int i;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number between %d and %d>\n", argv[0], MIN_NUMBER, MAX_NUMBER);
        return 1;
    }

    printf("Calculate the sum of n numbers with multiple threads\n");
    n = strtoul(argv[1], NULL, 10);
    if (n < MIN_NUMBER || n > MAX_NUMBER)
    {
        fprintf(stderr, "Error: Number must be between %d and %d.\n", MIN_NUMBER, MAX_NUMBER);
        return 1;
    }

    int max_threads = (n / MAX_SIZE) + (n % MAX_SIZE ? 1 : 0);
    pthread_t threads[max_threads];
    ThreadData thread_data[max_threads];
    int thread_count = 0;

    for (start = 1; start<= n; start += MAX_SIZE)
    {
        thread_data[thread_count].start = start;
        thread_data[thread_count].end = (start + MAX_SIZE - 1 <= n) ? (start + MAX_SIZE - 1) : n;
        pthread_create(&threads[thread_count], NULL, sum_range, &thread_data[thread_count]);
        thread_count++;
    }

    for (i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].result;
    }

    printf("The sum of the first %lu numbers is: %lu\n", n, total_sum);

    return 0;
}
