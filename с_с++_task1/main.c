#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
//#define __STDC_FORMAT_MACROS
//#include <stdint.h>
#include <inttypes.h>

//#define MIN_INT -2147483648

/*
Составить программу поиска M наибольших чисел в заданном массиве целых (типа int) чисел A длины N.
Числа M, N и элементы массива A подаются на стандартный ввод программы в следующем порядке:
N
A1 A2 ... AN
M
 */

int* search(const int *array, size_t n, size_t m) {
    char *keys = (char*) malloc(n);
    if (!keys) return NULL;
    memset(keys, '1', n);
    int *result = (int *) malloc(m*sizeof(int));
    if (!result) return NULL;
    int i = 0;
    int max, max_index;
    while (i < m) {
        int tmp_index = 0;
        while (1) {
            if (keys[tmp_index] == '1') break;
            tmp_index++;
        }
        max_index = tmp_index;
        max = array[max_index];
        for (int j = max_index; j < n; j++)
            if ((array[j] > max) && (keys[j] == '1')) {
                max = array[j];
                max_index = j;
            }
        result[i] = max;
        keys[max_index] = '0';
        i++;
    }
    free(keys);
    return result;
}

int main(int argc, char *argv[])
{
    int tmp_n = 0;
    if (scanf("%d", &tmp_n) != 1) {
        printf("[error]");
        return 0;
    }
    if (tmp_n <= 0) {
        printf("[error]");
        return 0;
    }
    size_t n = (size_t)tmp_n;

    int *array = (int *) malloc(n*sizeof(int));
    if (!array) {
        printf("[error]");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        int tmp;
        int64_t tmp64;
        if ((scanf("%" PRId64, &tmp64) != 1) || (errno == ERANGE)) {
            printf("[error]");
            free(array);
            return 0;
        }
        tmp = (int)tmp64;
        if (tmp64 != (int64_t)tmp) {
            printf("[error]");
            free(array);
            return 0;
        }
        array[i] = tmp;
    }

    int tmp_m = 0;
    if (scanf("%d", &tmp_m) != 1) {
        printf("[error]");
        free(array);
        return 0;
    }
    if (tmp_m < 0 || tmp_m > n) {
        printf("[error]");
        free(array);
        return 0;
    }
    size_t m = (size_t)tmp_m;

    if (m == 0) {
        free(array);
        return 0;
    }

    int *result = search(array, n, m);
    if (!result) {
        printf("[error]");
        free(array);
        return 0;
    }
    for (int i = 0; i < m; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    free(array);
    return 0;
}
