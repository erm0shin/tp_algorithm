/*Задача 1.6. Дан массив целых чисел A[0..n). Не используя других массивов переставить
  элементы массива A в обратном порядке за O(n).*/

#include <iostream>
#include <algorithm>
#include <assert.h>

void reverse( int n, int *array )
{
    assert( n > 0 );
    int middle = n / 2;
    for ( int i = 0; i < middle; i++ ) {
        std::swap( array[i], array[n - i - 1] );
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    int *array = new int[n];
    for( int i = 0; i < n; i++ ) {
        std::cin >> array[i];
    }
    reverse( n, array );
    for( int i = 0; i < n; i++ ) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    delete [] array;
    return 0;
}