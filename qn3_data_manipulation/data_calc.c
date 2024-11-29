#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ROWS 100
// MAX_VAL is the maximum temp value that should be in csv file
#define MAX_VAL 100


/**
 * struct temps_s - structure to store all average temperatures
 * @temps_arr: array of temperatures
 * @size: size of temp_arr
 * @nb_temps: number of temperature in array
 */
typedef struct temps_s
{
    int *temps_arr;
    int size;
    int nb_temps;
} temps_t;

/**
 * create_temps - creates a temps_t struct
 * Return: pointer to temps else NULL on failure
 */
temps_t *create_temps(void)
{
    temps_t *new_temps = malloc(sizeof(temps_t));
    if (!new_temps)
    {
        perror("Failed to allocate memory for temps_t");
        return NULL;
    }
    new_temps->size = 2;
    new_temps->nb_temps = 0;
    new_temps->temps_arr = malloc(new_temps->size * sizeof(int));
    if (!new_temps->temps_arr)
    {
        perror("Failed to allocate memory for temps array");
        free(new_temps);
        return NULL;
    }
    return new_temps;
}


/**
 * extract_data - extracts average temperatures from a csv file
 * @filename: name of csv file
 * @temps: pointer to temps strucuture
 * Return: 1 on success else 0 on failure
 */
int extract_data(char *filename, temps_t *temps)
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    if (!filename || !temps)
        return 0;
    file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open file");
        return 0;
    }
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line,"\n")] =  '\0';

        char *token = strtok(line, ",");
        int word_count = 1;

        while (token != NULL)
        {
            if (token[0] == '"') token++;
            if (token[strlen(token) - 1] == '"') token[strlen(token) - 1] = '\0';

            if (word_count == 11)
            {
                if (temps->nb_temps == temps->size)
                {
                    int *new_arr = realloc(temps->temps_arr, temps->size * 2 * sizeof(int));
                    if (!new_arr)
                    {
                        perror("Failed to reallocate memory");
                        fclose(file);
                        return 0;
                    }
                    temps->temps_arr = new_arr;
                    temps->size *= 2;
                }
                temps->temps_arr[temps->nb_temps++] = atoi(token);
                break;
            }
            token = strtok(NULL, ",");
            word_count++;
        }
    }
    fclose(file);

    // for (int i = 0; i < temps->nb_temps; i++) {
    //     printf("Row %d: %d\n", i + 1, temps->temps_arr[i]);
    // }
    return 1;
}

/**
 * find_mode : find the mode of integers in an array
 * temps: pointer to temps structure
 * Return: mode else 0 on error
 */
int find_mode(temps_t *temps)
{
    int mode, max_freq, i;
    if (!temps || temps->nb_temps == 0)
        return 0;
    int *freq = calloc(MAX_VAL, sizeof(int));
    if (!freq)
    {
        perror("Could not allocate memory for frequency array");
        return 0;
    }
    mode = 0;
    max_freq = 0;
    for (i = 0; i < temps->nb_temps; i++)
    {
        if (temps->temps_arr[i] < 0 || temps->temps_arr[i] >= MAX_VAL)
        {
            fprintf(stderr, "Value out of range %d\n", temps->temps_arr[i]);
            free(freq);
            return 0;
        }
        freq[temps->temps_arr[i]]++;
        if (freq[temps->temps_arr[i]] > max_freq)
        {
            max_freq = freq[temps->temps_arr[i]];
            mode = temps->temps_arr[i];
        }
    }
    return mode;
}

/**
 * mode - calculates the mode temperature from dataset
 * @self: object
 * @args: arguments
 * Return: pointer to solution
 */
static PyObject *mode(PyObject *self, PyObject *args)
{
    char *filename;
    temps_t *temps;
    int mode_val;
    if (!PyArg_ParseTuple(args, "s", filename))
        return NULL;
    temps = create_temps();
    if (!temps)
        return PyErr_NoMemory();
    if (!extract_data(filename, temps))
    {
        free(temps->temps_arr);
        free(temps);
        return PyErr_Format(PyExc_RuntimeError, "Failed to extract data");
    }
    mode_val = find_mode(temps);
    free(temps->temps_arr);
    free(temps);

    if (mode_val == 0)
        return PyErr_Format(PyExc_RuntimeError, "Could not calculate mode");

    return PyLong_FromLong(mode);
}
