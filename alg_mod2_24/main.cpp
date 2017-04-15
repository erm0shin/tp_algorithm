/*
2_4. Скользящий максимум.
Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некотрого окна
(последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для
каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n
log n), память O(k).
Формат входных данных.​ Вначале вводится n - количество элементов массива. Затем вводится n
строк со значением каждого элемента. Затем вводится k - размер окна.
Формат выходных данных.​ Разделенные пробелом значения максимумов для каждого положения
окна.
 */

#include <iostream>
#include <vector>

typedef struct node {
    int value;
    int init_index;
    node(): value(0), init_index(0) {};
    node(int input_val, int input_ind): value(input_val), init_index(input_ind) {};
    node(const struct node& input) { value = input.value; init_index = input.init_index; }
} Node;

bool Greater(const Node& first, const Node& second) {
    return first.value > second.value;
}

bool check_index(const Node& elem, int index) {
    return elem.init_index < index;
}

template <class T>
class Heap {
public:
    Heap() {};
    void push(T input) { heap.push_back(input); }
    void BuildHeap(bool (comparer)(const T&, const T&));
    void Add(int element, int index, bool (comparer)(const T&, const T&));
    const T& ShowMax(int cur_begin_of_window, bool (comparer)(const T&, const T&), bool (check_index)(const T&, int));
private:
    std::vector<T> heap;
    void SiftDown(int i, bool (comparer)(const T&, const T&));
    void SiftUp(int i, bool (comparer)(const T&, const T&));
    void ExtractMax(bool (comparer)(const T&, const T&));
};

// Проталкивание элемента вниз
template <class T>
void Heap<T>::SiftDown (int i, bool (comparer)(const T&, const T&)) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
    int largest = i;
    if (left < heap.size() && comparer(heap[left], heap[i]))
        largest = left;
    if (right < heap.size() && comparer(heap[right], heap[largest]))
        largest = right;
// Если больший сын есть, то проталкиваем корень в него.
    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        SiftDown(largest, comparer);
    }
}

// Проталкивание элемента наверх.
template <class T>
void Heap<T>::SiftUp (int i, bool (comparer)(const T&, const T&)) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!comparer(heap[i], heap[parent]))
            return;
        std::swap(heap[i], heap[parent]);
        i = parent;
    }
}

// Построение кучи.
template <class T>
void Heap<T>::BuildHeap (bool (comparer)(const T&, const T&)) {
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        SiftDown(i, comparer);
    }
}

// Добавление элемента.
template <class T>
void Heap<T>::Add (int element, int index, bool (comparer)(const T&, const T&)) {
    T tmp(element, index);
    //arr.push_back(tmp);
    this->push(tmp);
    SiftUp(heap.size() - 1, comparer);
}

// Извлечение максимального элемента.
template <class T>
void Heap<T>::ExtractMax (bool (comparer)(const T&, const T&)) {
    heap[0] = heap.back();
    heap.pop_back();
// Вызываем SiftDown для корня.
    if (!heap.empty()) {
        SiftDown(0, comparer);
    }
}

template <class T>
const T& Heap<T>::ShowMax (int cur_begin_of_window, bool (comparer)(const T&, const T&), bool (check_in)(const T&, int)) {
    while (check_in(heap[0], cur_begin_of_window)) {
        ExtractMax(comparer);
    }
    return heap[0];
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> array;
    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        array.push_back(tmp);
    }
    int k = 0;
    std::cin >> k;
    Heap<Node> heap;
    for (int i = 0; i < k; i++) {
        Node tmp(array[i], i);
        heap.push(tmp);
    }
    heap.BuildHeap(Greater);
    Node tmp = heap.ShowMax(0, Greater, check_index);
    std::cout << tmp.value << " ";
    for (int i = k; i < n; i++) {
        heap.Add(array[i], i, Greater);
        tmp = heap.ShowMax(i - k + 1, Greater, check_index);
        std::cout << tmp.value << " ";
    }
    return 0;
}