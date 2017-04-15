/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется
найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом
k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном
направлении.
4_2. ​ Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

#include <iostream>
#include <vector>

bool greater(const int &a, const int &b) {
    return a >= b;
}

//Устанавливаем медиану в начало массива
template <class T>
void Median(std::vector<T> &array, int left, int right, bool comparer(const T&, const T&)) {
//    int mid = (left + right) / 2;
//    if (array[mid] > array[right]) std::swap(array[mid], array[right]);
//    if (array[left] < array[mid]) std::swap( array[left], array[mid]);
//    if (array[left] > array[right]) std::swap(array[left], array[right]);
    int mid = (left + right) / 2;
    if (comparer(array[mid], array[right])) std::swap(array[mid], array[right]);
    if (!comparer(array[left], array[mid])) std::swap( array[left], array[mid]);
    if (comparer(array[left], array[right])) std::swap(array[left], array[right]);
}

template <class T>
int Partition (std::vector<T> &array, int left, int right, bool comparer(const T&, const T&))
{
    Median(array, left, right, comparer);
    int i = right;
    int j = right;
    while (j > left) {
        while (!comparer(array[j], array[left]) && j > left) j--;
        while (comparer(array[j], array[left]) && j > left) {
            std::swap(array[j], array[i]);
            j--;
            i--;
        }
    }
    std::swap(array[left], array[i]);
    return i;
}

template <class T>
int Find_kStat (std::vector<T> &array, int k, bool comparer(const T&, const T&)) {
    int left = 0;
    int right = array.size() - 1;
    int pivot = Partition(array, left, right, comparer);
    while (pivot != k) {
        if (pivot < k) left = pivot + 1;
        else right = pivot - 1;
        pivot = Partition(array, left, right, comparer);
    }
    return array[pivot];
}

int main() {
    int n = 0, k = -1;
    std::cin >> n;
    std::cin >> k;
    std::vector<int> array;
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        std::cin >> tmp;
        array.push_back(tmp);
    }
    std::cout << Find_kStat(array, k, greater);
    return 0;
}