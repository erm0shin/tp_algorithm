/*
6_1. MSD для строк.
Дан массив строк. Количество строк не больше 10​ 5​ . Отсортировать массив методом поразрядной
сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
 */

#include <iostream>
#include <vector>
#include <cstring>
#define ALPH 256

int get_char(char * const & str, int k) {
    return str[k];
}

template <class T>
void counting_sort(T *a, int n, int k, int *cnt, int (get_digit)(const T&, int)) {
    for (int i = 0; i < ALPH; ++i) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        cnt[get_digit(a[i], k)]++;
    }
    int sum = 0;
    for (int i = 0; i < ALPH; ++i) {
        int tmp = cnt[i];
        cnt[i] = sum;
        sum += tmp;
    }
    T *res = new T[n];
    for (int i = 0; i < n; ++i) {
        res[cnt[get_digit(a[i], k)]] = a[i];
        cnt[get_digit(a[i], k)]++;
    }
    memcpy(a, res, n * sizeof(T));
    delete[] res;
}

template <class T>
void msd_sort(T *a, int n, int k, int (get_digit)(const T&, int)) {
    int *groups = new int[ALPH + 1];
    groups[ALPH] = n;
    counting_sort(a, n, k, groups, get_digit);
    for (int i = 0; i < ALPH; ++i) {
        int group_size = groups[i + 1] - groups[i];
        if (group_size > 1) {
            msd_sort(&a[groups[i]], group_size, k + 1, get_digit);
        }
    }
    delete[] groups;
}

int main() {
    std::vector<char *> array;
    std::string str;
    while (std::cin >> str) {
        char *c_str = new char[str.length() + 1];
        strcpy(c_str, str.c_str());
        array.push_back(c_str);
    }
    msd_sort(&array[0], array.size(), 0, get_char);
    for (int i = 0; i < array.size(); i++) std::cout << array[i] << std::endl;
    for (int i = 0; i < array.size(); i++) delete [] array[i];
    return 0;
}