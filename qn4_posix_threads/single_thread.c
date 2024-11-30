#include <stdio.h>
#include <stdlib.h>

/**
 * main - calculates the sum of n numbers using a single thread
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, else 1 on failure
 */
int main(int argc, char *argv[])
{
    unsigned long n, i;
    unsigned long sum = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number between 200 and 2000>\n", argv[0]);
        return 1;
    }

    n = strtoul(argv[1], NULL, 10);
    if (n < 200 || n > 2000)
    {
        fprintf(stderr, "Error: Number must be between 200 and 2000.\n");
        return 1;
    }

    for (i = 1; i <= n; i++)
        sum += i;

    printf("The sum of %lu numbers is: %lu\n", n, sum);
    return 0;
}
