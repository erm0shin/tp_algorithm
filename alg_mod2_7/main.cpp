#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

/*
// Возвращает индекс, на который встанет пивот после разделения.
int Partition1(int* a, int n) {
    if (n <= 1) {
        return 0;
    }
    const int& pivot = a[n - 1];
    int i = 0, j = n - 2;
    while (i <= j) {
        for ( ; a[i] < pivot; ++i ) {}
        for ( ; j >= 0 && !( a[j] < pivot ); --j ) {}
        if( i < j ) {
            std::swap(a[i++], a[j--]);
        }
    }
    std::swap(a[i], a[n - 1]);
    return i;
}
void QuickSort1(int* a, int n) {
    int part = Partition1(a, n);
    if (part > 0) QuickSort1(a, part);
    if (part + 1 < n) QuickSort1(a + part + 1, n - (part + 1));
}
 */











/*
//Устанавливаем медиану в конец массива
void Median2(int *array, int left, int right) {
    int mid = (left + right) / 2;
    if (array[mid] > array[right]) std::swap(array[mid], array[right]);
    if (array[left] < array[mid]) std::swap( array[left], array[mid]);
    if (array[left] < array[right]) std::swap(array[left], array[right]);
}

// Возвращает индекс, на который встанет пивот после разделения.
int Partition2(int* a, int n) {
    if (n <= 1) {
        return 0;
    }
    Median2(a, 0, n - 1);
    const int& pivot = a[n - 1];
    int i = 0, j = n - 2;
    while (i <= j) {
        for ( ; a[i] < pivot; ++i ) {}
        for ( ; j >= 0 && !( a[j] < pivot ); --j ) {}
        if( i < j ) {
            std::swap(a[i++], a[j--]);
        }
    }
    std::swap(a[i], a[n - 1]);
    return i;
}
void QuickSort2(int* a, int n) {
    int part = Partition2(a, n);
    if (part > 0) QuickSort2(a, part);
    if (part + 1 < n) QuickSort2(a + part + 1, n - (part + 1));
}*/












/*
//Устанавливаем медиану в начало массива
void Median3(int *array, int left, int right) {
    int mid = (left + right) / 2;
    if (array[mid] > array[right]) std::swap(array[mid], array[right]);
    if (array[left] < array[mid]) std::swap( array[left], array[mid]);
    if (array[left] > array[right]) std::swap(array[left], array[right]);
}

int Partition3(int *array, int left, int right)
{
    Median3(array, left, right);
    int i = right;
    int j = right;
    while (j > left) {
        while (array[j] < array[left] && j > left) j--;
        while (array[j] >= array[left] && j > left) {
            std::swap(array[j], array[i]);
            j--;
            i--;
        }
    }
    std::swap(array[left], array[i]);
    return i;
}

void QuickSort3(int* a, int left, int right) {
    int part = Partition3(a, left, right);
    if (part > 0) QuickSort3(a, 0, part - 1);
    if (part + 1 < right) QuickSort3(a + part + 1, 0, right - (part + 1));
}*/










/*
// Возвращает индекс, на который встанет пивот после разделения.
int Partition4(int* a, int n) {
    if (n <= 1) {
        return 0;
    }
    const int& pivot = a[n - 1];
    int i = 0, j = n - 2;
    while (i <= j) {
        for ( ; a[i] < pivot; ++i ) {}
        for ( ; j >= 0 && !( a[j] < pivot ); --j ) {}
        if( i < j ) {
            std::swap(a[i++], a[j--]);
        }
    }
    std::swap(a[i], a[n - 1]);
    return i;
}

void insertion_sort4(int *array, int l, int r) {
    for (int i = l; i < r; i++) {
        int tmp = array[i];
        int j;
        for (j = i - 1; j >= 0 && tmp < array[j]; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = tmp;
    }
}

void QuickSort4(int* a, int n) {
    if (n <= 15) {
        insertion_sort4(a, 0, n);
        return;
    }
    int part = Partition4(a, n);
    if (part > 0) QuickSort4(a, part);
    if (part + 1 < n) QuickSort4(a + part + 1, n - (part + 1));
}
 */









// Возвращает индекс, на который встанет пивот после разделения.
int Partition5(int* a, int from, int to) {
    if (to - from <= 0) {
        return 0;
    }
    const int& pivot = a[to];
    int i = from, j = to - 1;
    while (i <= j) {
        for ( ; a[i] < pivot; ++i ) {}
        for ( ; j >= 0 && !( a[j] < pivot ); --j ) {}
        if( i < j ) {
            std::swap(a[i++], a[j--]);
        }
    }
    std::swap(a[i], a[to]);
    return i;
}

void insertion_sort5(int *array, int l, int r) {
    for (int i = l; i <= r; i++) {
        int tmp = array[i];
        int j;
        for (j = i - 1; j >= l && tmp < array[j]; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = tmp;
    }
}

void QuickSort5(int* a, int from, int to) {
    if (to - from <= 15) {
        insertion_sort5(a, from, to);
        return;
    }
    int part = Partition5(a, from, to);
    if (part > 0) QuickSort5(a, from, part);
    if (part + 1 < to - from) QuickSort5(a + part + 1, part + 1, to);
}

void Sort5(int *a, int from, int to) {
    while (to - from > 0) {
        int PivotPos = Partition5(a,from, to);
        if ((to - PivotPos) > (PivotPos - from)) {
            QuickSort5(a, from, PivotPos);
            from = PivotPos + 1;
        }
        else {
            QuickSort5(a, PivotPos, to);
            to = PivotPos - 1;
        }
    }
}



int main() {
    /*freopen("data.txt", "w", stdout);
    for (int i = 0; i < 25000000; i++) {
        std::cout << rand() % 4000000 - 2000000 << " ";
    }*/

    std::vector<int> array;

    freopen("data.txt", "r", stdin);


    /*for (int i = 0; i < 100; i++) {
        int tmp;
        std::cin >> tmp;
        array.push_back(tmp);
    }*/

    int tmp;
//    while (std::cin >> tmp) {
//        array.push_back(tmp);
//    }
    for (int i = 0; i < 2000; i++) {
        std::cin >> tmp;
        array.push_back(tmp);
    }

    /*clock_t start_time = clock();
    QuickSort1(&array[0], array.size());
    clock_t finish_time = clock();
    std::cout << (float)(finish_time - start_time) / CLOCKS_PER_SEC;*/
    //Изначальный QuickSort потребовал 4.65 s

    /*clock_t start_time = clock();
    QuickSort2(&array[0], array.size());
    clock_t finish_time = clock();
    std::cout << (float)(finish_time - start_time) / CLOCKS_PER_SEC;*/
    //Оптимизация выбора опорного элемента - 4.68 s
    //Одна только оптимизация выбора опорного элемента улучшений не дала
    //она даже немного ухудшила время выполнения (на 0.03 s)

    /*clock_t start_time = clock();
    QuickSort3(&array[0], 0, array.size() - 1);
    clock_t finish_time = clock();
    std::cout << (float)(finish_time - start_time) / CLOCKS_PER_SEC;*/
    //Другая реализация Partition и выбора опорного элемента только ухудшили
    //время выполнения (6.56 s)
    //Поэтому вернемся к изначальному Partition

    //Гибридная сортировка
//    clock_t start_time = clock();
//    QuickSort4(&array[0], array.size());
//    clock_t finish_time = clock();
//    std::cout << (float)(finish_time - start_time) / CLOCKS_PER_SEC;
    //для n = 10 - 4.40 s
    //для n = 50 - 4.54 s
    //для n = 15 - 4.38 s
    //Оптимальное количество элементов для InsertionSort - 15 элементов

    //Убрали частично рекурсию
//    clock_t start_time = clock();
    Sort5(&array[0], 0, array.size() - 1);
//    clock_t finish_time = clock();
//    std::cout << (float)(finish_time - start_time) / CLOCKS_PER_SEC;

//    for (int i = 10; i <= array.size(); i += 10) {
//        std::cout << array[i - 1] << " ";
//    }
//    std::cout << std::endl;
//    for (int i = 0; i < array.size(); i++) {
//        std::cout << array[i] << " ";
//    }
    return 0;
}