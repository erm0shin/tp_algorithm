/*
 Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды
push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры
данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не
оправдалось, то напечатать NO.
 4_3. ​ Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью
динамического буфера.
 */

#include <iostream>

// Класс «Динамический массив».
class CArray {
public:
    CArray() : buffer(NULL), bufferSize(0), realSize(0), default_size(3) {}
    ~CArray() { delete[] buffer; }
// Доступ по индексу.
    int operator[]( int index ) { return buffer[index]; }
// Добавление нового элемента.
    void add(int element);
    void dec() {realSize--;}
private:
    int* buffer; // Буфер.
    int bufferSize; // Размер буфера.
    int realSize; // Количество элементов в массиве.
    void grow();
    const int default_size;
};

// Увеличение буфера.
void CArray::grow()
{
    int newBufferSize = std::max( bufferSize * 2, default_size );
    int* newBuffer = new int[newBufferSize];
    for( int i = 0; i < realSize; ++i )
        newBuffer[i] = buffer[i];
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

// Добавление элемента.
void CArray::add(int element)
{
    if( realSize == bufferSize )
        grow();
    buffer[realSize++] = element;
}

// Стек целых чисел, реализованный с помощью массива.
class CStack {
public:
    CStack();
// Добавление и извлечение элемента из стека.
    void push(int a);
    int pop();
// Проверка на пустоту.
    bool is_empty() { return top == -1; }
private:
    CArray buffer;
    int bufferSize;
    int top; // Индекс верхнего элемента.
};

CStack::CStack(): bufferSize(0), top(-1)
{
    CArray buffer; // Создаем буфер.
}

// Добавление элемента.
void CStack::push(int a)
{
    top++;
    buffer.add(a);
}

// Извлечение элемента.
int CStack::pop()
{
    top--;
    buffer.dec();
    return buffer[top+1];
}

class CQueue {
public:
    CQueue() {}
    void push_back(int input);
    //bool pop_front(int input);
    int pop_front();
private:
    CStack stack_push;
    CStack stack_pop;
};

void CQueue::push_back(int input) {
    stack_push.push(input);
}

/*bool CQueue::pop_front(int input) {
    if (stack_pop.is_empty()) {
        while (!stack_push.is_empty())
            stack_pop.push(stack_push.pop());
    }
    if (stack_pop.is_empty()) {
        if (input == -1) return true;
        else return false;
    }
    if (stack_pop.pop() == input) return true;
    else return false;
}*/

int CQueue::pop_front() {
    if (stack_pop.is_empty()) {
        while (!stack_push.is_empty())
            stack_pop.push(stack_push.pop());
    }
    if (stack_pop.is_empty()) return -1;
    else return stack_pop.pop();
}

bool analysis(int a, int b, CQueue &myqueue) {
    switch (a) {
        case 2: {
            if (myqueue.pop_front() == b) return true;
            else return false;
        }
        case 3: {
            myqueue.push_back(b);
            return true;
        }
    }
    /*if (a == 2) return myqueue.pop_front(b);
    if (a == 3) {
        myqueue.push_back(b);
        return true;
    }*/
    return false;
}

int main() {
    CQueue myqueue;
    int n = 0, i = 0;
    bool result = true;
    std::cin >> n;
    if ((n < 0) || (n > 1000000)) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    while (i != n) {
        int a = 0;
        int b = 0;
        std::cin >> a >> b;
        if (!analysis(a, b, myqueue)) result = false;
        i++;
    }
    if (result) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;
    return 0;
    // не работает набор 5 3 5 2 5 2 -1 3 1 2 1
}