#include <iostream>
#include <vector>
#include <cstring>

bool isLess(const std::string &first, const std::string &second) {
    return first.compare(second) <= 0;
}

template <class T>
void insertion_sort(T *array, int l, int r, bool (comparer)(const T&, const T&)) {
    for (int i = l; i < r; i++) {
        T tmp = array[i];
        int j;
        for (j = i - 1; j >= 0 && comparer(tmp, array[j]); --j ) {
            array[j + 1] = array[j];
        }
        array[j + 1] = tmp;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> array;
    std::string buf;
    for (int i = 0; i < n; i++) {
        std::cin >> buf;
        array.push_back(buf);
    }
    insertion_sort(&array[0], 0, n, isLess);
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << std::endl;
    }
    return 0;
}