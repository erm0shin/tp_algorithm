/*Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество
таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).*/

#include <iostream>
#include <assert.h>

int count_sum( int n, int *A, int m, int *B, int k )
{
    assert( n > 0 );
    assert( m > 0 );
    int result = 0, first_index = 0;
    for( int j = m - 1; j >= 0; j-- ) {
        for( int i = first_index; i < n; i++ ) {
            int tmp = B[j] + A[i];
            if( tmp == k ) result++;
            if( tmp > k ) {
                first_index = i;
                break;
            }
        }
    }
    return result;
}

int main() {
    int n = 0;
    std::cin >> n;
    int *A = new int [n];
    for( int i = 0; i < n; i++ ) {
        std::cin >> A[i];
    }
    int m = 0;
    std::cin >> m;
    int *B = new int [m];
    for( int j = 0; j < m; j++ ) {
        std::cin >> B[j];
    }
    int k = 0;
    std::cin >> k;
    std::cout << count_sum( n, A, m, B, k ) << std::endl;
    delete [] A;
    delete [] B;
    return 0;
}