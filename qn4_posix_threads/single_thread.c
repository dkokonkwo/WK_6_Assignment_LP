#include <stdio.h>

/**
 * main - calculates the sum of n numbers usins a single thread
 * Return: 0 on succes else 1 on failure
 */
int main(void)
{
    unsigned long n, i;
    unsigned long sum = 0;

    printf("Calculate the sum of n numbers\n");
    while (1)
    {
        printf("Enter a number between 200 and 2000: ");
        if (scanf("%lu", &n) != 1 || n <= 200 || n > 2000)
        {
            printf("Invalid input.Please try again.\n");
            while (getchar() != '\n');
        }
        else
            break;
    }
    for (i = 1; i <= n; i++)
        sum += i;
    printf("The sum of %lu numbers is: %lu\n", n, sum);
    return 0;
}