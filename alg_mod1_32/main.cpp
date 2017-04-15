/*​ Задача 3.2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго
возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m).*/

#include <iostream>
#define pow 4

int binary_search( int begin_index, int end_index, int *A )
{
    int left = begin_index, right = end_index, middle = ( right - left ) / 2;
    //алгоритм похож на метод дихотомического поиска
    while( ( left + 1 ) < right ) {
        if( A[middle] > A[middle - 1] ) {
            if( A[middle] < A[middle + 1] ) left = middle;
            else return middle;
        }
        else right = middle;
        middle = ( right - left ) / 2 + left;
    }
    //проверяю особые случаи, когда A[left] и A[right] - соседние элементы
    //так как возможно разыменование не своей области памяти
    //например A = {1, 2}, тогда происходит разыменование A[-1]
    if( A[left] < A[right] ) return right;
    else return left;
}

int split(int n, int *A){
    int begin_index = 0, end_index;
    if (n > pow) end_index = pow;
    else end_index = n - 1;
    while (true)
        if (A[end_index] > A[end_index+1] || A[end_index] < A[end_index - 1]) {
            return binary_search(begin_index, end_index, A);
        }
        else {
            begin_index = end_index;
            end_index *=pow;
            if (end_index >= n) end_index = n - 1;
        }
}

int main() {
    int n = 0;
    std::cin >> n;
    int *A = new int [n];
    for( int i = 0; i < n; i++ ) {
        std::cin >> A[i];
    }
    std::cout << split( n, A ) << std::endl;
    delete [] A;
    return 0;
}