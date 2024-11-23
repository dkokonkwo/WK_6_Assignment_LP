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
int main(void)
{
    unsigned long n, start, total_sum = 0;
    int i;
    pthread_t threads[(MAX_NUMBER - MIN_NUMBER + 1) / MAX_SIZE];
    ThreadData thread_data[(MAX_NUMBER - MIN_NUMBER + 1) /MAX_SIZE];
    int thread_count = 0;

    printf("Calculate the sum of n numbers with multiple threads\n");
    while (1)
    {
        printf("Enter a number between 200 and 2000: ");
        if (scanf("%lu", &n) != 1 || n <= MIN_NUMBER || n > MAX_NUMBER)
        {
            printf("Invalid input.Please try again.\n");
            while (getchar() != '\n');
        }
        else
            break;
    }

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
