#include <stdio.h>
#include <stdlib.h>
#include "stringsort.h"

/**
 * main - tests string manipulator code
 * @argc: num of arguments
 * @argv: arguments array
 * Return: EXIT_SUCCESS else EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <namesfile.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("%s\n", argv[1]);
    if (!count_n_sort(argv[1]))
    {
        fprintf(stderr, "An error occurred while processing the file.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}