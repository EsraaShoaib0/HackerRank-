#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'runningMedian' function below.
 *
 * The function is expected to return a DOUBLE_ARRAY.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

/*
 * To return the double array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * double* return_double_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static double a[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 *
 *     return a;
 * }
 *
 * double* return_double_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     double* a = malloc(5 * sizeof(double));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1.1;
 *     }
 *
 *     return a;
 * }
 *
 */
double* runningMedian(int a_count, int* a, int* result_count) {
     int sort_arr[a_count];
  double *median = malloc (a_count * sizeof(double));

  sort_arr[0] = a[0];
  median[0] = (double)a[0];
  for (int i = 1; i < a_count; i++)
  { 
    int j = i;
    if (a[i] < sort_arr[i-1])
    {
      while (a[i] < sort_arr[j-1])
      {
        if (j == 0)
        {
          break;
        }
        j--;
      }
      memmove (&sort_arr[j+1], &sort_arr[j], (i-j)*sizeof(int));
    }
    sort_arr[j] = a[i];

    if ((i % 2) == 1) {
      median[i] = ((double)sort_arr[i/2+1]+(double)sort_arr[i/2])/2;
    }
    else {
      median[i] = (double)sort_arr[i/2];
    }
  }
  *result_count = a_count;
  return median;
}
            
        
    
    
    


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int a_count = parse_int(ltrim(rtrim(readline())));

    int* a = malloc(a_count * sizeof(int));

    for (int i = 0; i < a_count; i++) {  //a_count = dimensione array
        int a_item = parse_int(ltrim(rtrim(readline())));

        *(a + i) = a_item;
    }

    int result_count;
    double* result = runningMedian(a_count, a, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%lf", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
