/*
 7_1.​ ​ Атлеты.
В город ​ N приехал цирк с командой атлетов. Они хотят удивить горожан города ​ N — выстроить из своих тел
башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д.
Каждый атлет характеризуется силой ​ s i (kg) и массой ​ m i (kg). Сила — это максимальная масса, которую
атлет способен держать у себя на плечах.
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
программу, которая определит максимальную высоту башни, которую они могут составить.
Известно, что если атлет тяжелее, то он и сильнее:
если ​ m i > ​ m j , то ​ s i > ​ s j .
Атлеты равной массы могут иметь различную силу.
Формат входных данных:
Вход содержит только пары целых чисел ​ — массу и силу атлетов. Число атлетов 1 ≤ ​ n ≤ 100000. Масса и
сила являются положительными целыми числами меньше, чем 2000000.
Формат выходных данных:
Выход должен содержать натуральное число — максимальную высоту башни.
 */

#include <iostream>
#include <algorithm>

// Класс «Динамический массив».
class vector {
public:
    vector() : buffer(NULL), bufferSize(0), realSize(0), default_size(3) {}
    vector(int buf) : buffer(NULL), bufferSize(buf), realSize(0), default_size(3) {}
    ~vector() { delete[] buffer; }
// Размер.
    int get_size() const { return realSize; }
// Доступ по индексу.
    int operator[]( int index ) { return buffer[index]; }
    int* at(int index) { return &buffer[index]; }
// Добавление нового элемента.
    void add(int element);
private:
    int* buffer; // Буфер.
    int bufferSize; // Размер буфера.
    int realSize; // Количество элементов в массиве.
    void grow();
    const int default_size;
};

// Увеличение буфера.
void vector::grow()
{
    int newBufferSize = std::max( bufferSize * 2, default_size );
    int* newBuffer = new int[newBufferSize];
    for( int i = 0; i < realSize; ++i )
        newBuffer[i] = buffer[i];
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

void vector::add(int element)
{
    if( realSize == bufferSize )
        grow();
    buffer[realSize++] = element;
}

void sort(vector & vec1, vector & vec2) {
    for (int i = 0; i < vec1.get_size() - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < vec1.get_size(); j++)
            if (vec1[j] < vec1[min_index]) min_index = j;
        if (min_index != i) {
            int tmp;
            tmp = *vec1.at(i);
            *vec1.at(i) = *vec1.at(min_index);
            *vec1.at(min_index) = tmp;
            tmp = *vec2.at(i);
            *vec2.at(i) = *vec2.at(min_index);
            *vec2.at(min_index) = tmp;
        }
    }
}

int max_height (vector & weight, vector & power) {
    int cur_weight = weight[0], cur_height = 1;
    for(int i = 1; i < weight.get_size(); i++) {
        if(power[i] >= cur_weight) {
            cur_weight += weight[i];
            cur_height++;
        }
    }
    return cur_height;
}

int main() {
    vector weight, power;
    int a = 0, b = 0;
    while(std::cin >> a >> b) {
        weight.add(a);
        power.add(b);
    }
    sort(weight, power);
    std::cout << max_height(weight, power) << std::endl;
    return 0;
}