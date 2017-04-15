/*
5_3. Количество инверсий.
Дана последовательность целых чисел из диапазона (-10^9 .. 10^9). Длина последовательности не
больше 10^6. Числа записаны по одному в строке. Количество чисел не указано.
Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
 */

#include <stdint.h>
#include <memory.h>
#include <vector>
#include <iostream>

bool Less(const int &el1, const int &el2) {
    return el1 <= el2;
}

template <class T>
int64_t Merge(const T* a, int aLen, const T* b, int bLen, T* c, bool (*comparer)(const T&, const T&)) {
    int i = 0, j = 0;
    int64_t result = 0;
    while (i < aLen && j < bLen) {
        if (comparer(a[i], b[j])) {
            c[i + j] = a[i];
            i++;
        }
        else {
            c[i + j] = b[j];
            j++;
            result += aLen - i;
        }
    }
// Обработаем остаток.
    if (i == aLen) {
        while (j < bLen) {
            c[i + j] = b[j];
            j++;
        }
    }
    else {
        while (i < aLen) {
            c[i + j] = a[i];
            i++;
        }
    }
    return result;
}

template <class T>
void MergeSort(T *array, int aLen, T *new_array, int bufLen, bool (*comparer)(const T&, const T&), int64_t &result) {
    if (aLen <= 1) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(array, firstLen, new_array, bufLen, comparer, result);
    MergeSort(array + firstLen, secondLen, new_array, bufLen, comparer, result);
    result += Merge(array, firstLen, array + firstLen, secondLen, new_array, comparer);
    memcpy(array, new_array, sizeof(int) * aLen);
}

int main() {
    std::vector<int> array;
    int tmp = 0;
    while (std::cin >> tmp) {
        array.push_back(tmp);
    }
    int *new_array = new int[array.size()];
    int64_t result = 0;
    MergeSort(&array[0], array.size(), new_array, array.size(), Less, result);
    std::cout << result;
    delete [] new_array;
    return 0;
}