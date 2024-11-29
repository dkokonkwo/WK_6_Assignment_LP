#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_LINE_LENGTH 1024
// MAX_VAL is the maximum temp value that should be in csv file
#define MAX_VAL 101

/**
 * struct number - structure for an integer
 * @pos: postive number
 * @neg: negative number
 */
typedef struct number_s
{
    int pos;
    int neg;
} number;

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
 * create_num - creates a number struc
 * Return: pointer to number else NULL on failure
 */
number *create_num(void)
{
    number *new_num = malloc(sizeof(number));
    if (!new_num)
    {
        perror("Failed to create number");
        return NULL;
    }
    new_num->pos = 0;
    new_num->neg = 0;
    return new_num;
}

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
 * free_freq - frees the allocated memory for the freq array
 * @freq: array of number pointers
 */
void free_freq(number **freq)
{
    if (!freq)
        return;
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (freq[i])
            free(freq[i]);
    }
    free(freq);
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
        return -1;
    number **freq = calloc(MAX_VAL, sizeof(number *));
    if (!freq)
    {
        perror("Could not allocate memory for frequency array");
        return -2;
    }
    for (i = 0; i < MAX_VAL; i++)
    {
        freq[i] = create_num();
        if (!freq[i])
        {
            free_freq(freq);
            return -2;
        }
    }
    mode = 0;
    max_freq = 0;
    for (i = 0; i < temps->nb_temps; i++)
    {
        int value = temps->temps_arr[i];
        int index = abs(value);
        if (index >= MAX_VAL)
        {
            fprintf(stderr, "Value out of range %d\n", temps->temps_arr[i]);
            free_freq(freq);
            return -3;
        }
        if (value < 0 )
        {
            freq[index]->neg++;
            if (freq[index]->neg > max_freq)
            {
                max_freq = freq[index]->neg;
                mode = value;
            }
        }
        else
        {
            freq[index]->pos++;
            if (freq[index]->pos > max_freq)
            {
                max_freq = freq[index]->pos;
                mode = value;
            }
        }
    }
    free_freq(freq);
    return mode;
}

/**
 * compare - comparison funtion for qsort
 * a: first value
 * b: second value
 * Return: difference in value
 */
int compare(const void *a, const void *b)
{
    int int_a = *((int*)a);
    int int_b = *((int *)b);

    return int_a < int_b;
}

/**
 * find_median - finds the median integer from array of integers
 * @temps: pointer to temps structure
 * Return: median val else 0 on error
 */
double find_median(temps_t *temps)
{
    if (!temps)
        return 0;

    qsort(temps->temps_arr, temps->nb_temps, sizeof(int), compare);

    if (temps->nb_temps % 2 == 0)
    {
        return (temps->temps_arr[temps->nb_temps / 2 - 1] + temps->temps_arr[temps->nb_temps / 2]) / 2.0;
    }
    else
    {
        return temps->temps_arr[temps->nb_temps / 2];
    }
}

/**
 * cal_stddev - calculate the standard deviation of an array
 * @temps: pointer to temps structure
 * Return: standard deviation else 0 on error
 */
double cal_stddev(temps_t *temps)
{
    double mean, sum_of_squares, variance;
    int i;
    if (!temps || temps->nb_temps == 0)
        return 0;

    mean = 0;
    for (i = 0; i < temps->nb_temps; i++)
        mean += temps->temps_arr[i];
    mean /= temps->nb_temps;

    sum_of_squares = 0;
    for (i = 0; i < temps->nb_temps; i++)
        sum_of_squares += ((temps->temps_arr[i] - mean) * (temps->temps_arr[i] - mean));

    variance = sum_of_squares / temps->nb_temps;

    return sqrt(variance);
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
    if (!PyArg_ParseTuple(args, "s", &filename))
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

    if (mode_val == -1)
        return PyErr_Format(PyExc_RuntimeError, "No temps structure");

    else if (mode_val == -2)
        return PyErr_Format(PyExc_RuntimeError, "Could not create frequency array");

    else if (mode_val == -3)
        return PyErr_Format(PyExc_RuntimeError, "Value out of range");

    return PyLong_FromLong(mode_val);
}

/**
 * median - calculates the median temperature from dataset
 * @self: object
 * @args: arguments
 * Return: pointer to solution
 */
static PyObject *median(PyObject *self, PyObject *args)
{
    char *filename;
    temps_t *temps;
    double median_val;
    if (!PyArg_ParseTuple(args, "s", &filename))
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
    median_val = find_median(temps);
    free(temps->temps_arr);
    free(temps);

    if (median_val == 0)
        return PyErr_Format(PyExc_RuntimeError, "Could not calculate median");

    return PyFloat_FromDouble(median_val);
}

/**
 * standev - calculates the standard deviation from the mean temperature
 * @self: object
 * @args: arguments
 * Return: pointer to solution
 */
static PyObject *standev(PyObject *self, PyObject *args)
{
    char *filename;
    temps_t *temps;
    double stddev;
    if (!PyArg_ParseTuple(args, "s", &filename))
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
    stddev = cal_stddev(temps);
    free(temps->temps_arr);
    free(temps);

    if (stddev == 0)
        return PyErr_Format(PyExc_RuntimeError, "Could not calculate standard deviation");

    return PyFloat_FromDouble(stddev);
}

static PyMethodDef StatMethods[] = {
    {"mode", mode, METH_VARARGS, "Finds mode in array of numbers"},
    {"median", median, METH_VARARGS, "Finds median in array of numbers"},
    {"standev", standev, METH_VARARGS, "Calculates the standard deviation from array of numbers"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef statmodule = {
    PyModuleDef_HEAD_INIT,
    "dataman",
    "A module for statictical calculations",
    -1,
    StatMethods
};

PyMODINIT_FUNC PyInit_dataman(void)
{
    return PyModule_Create(&statmodule);
}