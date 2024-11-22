#ifndef STRINGSORT_H
#define STRINGSORT_H

int compare_names(const void *a, const void *b);
void sort_names(char *names[], int count);
int sorted_names(const char *filename, char *names[], int count);
int count_n_sort(const char *filename);

#endif