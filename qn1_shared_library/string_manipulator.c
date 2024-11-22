#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringsort.h"

#define MAX_NAMES 100
/**
 * compare_names - compares two names
 * @a: first name
 * @b: second name
 * Return: 0 if equal, -1 if a is less else, 1 if b is less
 */
int compare_names(const void *a, const void *b)
{
    const char *name1 = *(const char **)a;
    const char *name2 = *(const char **)b;
    return strcmp(name1, name2);
}

/**
 * sort_names - sort names in ascending order
 * @names: array of names
 * @count: number of names in array
 * Return: Nothing
 */
void sort_names(char *names[], int count)
{
    qsort(names, count, sizeof(char *), compare_names);
}

/**
 * sorted_names - add sorted names to file
 * @filename: filname of unsorted names
 * @names: array of names
 * @count: number of names in array
 * Return: 1 on success else 0 on failure
 */
int sorted_names(const char *filename, char *names[], int count)
{
    int i;
    FILE *file;
    char new_filename[256];

    if (!filename || count < 1)
        return 0;
    snprintf(new_filename, sizeof(new_filename), "sorted_%s", filename);
    file = fopen(new_filename, "w");
    if (!file)
    {
        perror("Could not open file");
        return 0;
    }
    for (i = 0; i < count; i++)
    {
        if (fputs(names[i], file) == EOF)
        {
            perror("Could not write to file");
            fclose(file);
            return 0;
        }
    }
    printf("Sorted names add to %s\n", new_filename);
    fclose(file);
    return 1;
}

/**
 * count_n_sort - counts and sorts full names in a file
 * @filename: name of file containing entries
 * Return: 1 on success else 0
 */
int count_n_sort(const char *filename)
{
    char *names[MAX_NAMES];
    char line[256];
    int count, i;
    FILE *file;
    if (!filename)
        return 0;
    file = fopen(filename, "r");
    if (!file)
    {
        perror("Could not open file");
        return 0;
    }
    count = 0;
    while (fgets(line, sizeof(line), file))
    {
        line[strspn(line, "\n")] = '\0';
        names[count] = strdup(line);
        count++;
    }
    fclose(file);
    sort_names(names, count);
    if (!sorted_names(filename, names, count))
    {
        perror("Could not add sorted names to file\n");
        return 0;
    }
    printf("%d entries in %s\n", count, filename);
    for (i = 0; i < count; i++) 
        free(names[i]);

    return 1;
}