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

typedef struct athlete {
    int weight;
    int power;
    athlete() : weight(0), power(0) {}
    athlete(const athlete &ath);
} athlete;

athlete::athlete(const athlete &ath) {
    weight = ath.weight;
    power = ath.power;
}

// Класс «Динамический массив».
class vector {
public:
    vector() : buffer(NULL), bufferSize(0), realSize(0), default_size(3) {}
    vector(int buf) : buffer(NULL), bufferSize(buf), realSize(0), default_size(3) {}
    ~vector() { delete[] buffer; }
// Размер.
    int get_size() const { return realSize; }
// Доступ по индексу.
    athlete& operator[]( int index ) { return buffer[index]; }
    //athlete* at(int index) { return &buffer[index]; }
// Добавление нового элемента.
    void add(int weight, int power);
    //athlete* get_buffer() { return buffer; }
private:
    athlete* buffer; // Буфер.
    int bufferSize; // Размер буфера.
    int realSize; // Количество элементов в массиве.
    void grow();
    const int default_size;
};

// Увеличение буфера.
void vector::grow()
{
    int newBufferSize = std::max( bufferSize * 2, default_size );
    athlete* newBuffer = new athlete[newBufferSize];
    for( int i = 0; i < realSize; ++i )
        newBuffer[i] = buffer[i];
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

void vector::add(int weight, int power)
{
    if( realSize == bufferSize ) grow();
    buffer[realSize].weight = weight;
    buffer[realSize].power = power;
    realSize++;
}

void swap(athlete &ath1, athlete &ath2) {
    athlete tmp = ath1;
    ath1 = ath2;
    ath2 = tmp;
}

int max_height(vector & ath) {
    int cur_weight = 0, cur_height = 0;
    for (int i = 0; i < ath.get_size() ; i++) {
        int min_index = i;
        for (int j = i ; j < ath.get_size(); j++)
            if (ath[j].weight <= ath[min_index].weight && ath[j].power < ath[min_index].power) min_index = j;
        if (min_index != i) swap(ath[i], ath[min_index]);
        if(ath[i].power >= cur_weight) {
            cur_weight += ath[i].weight;
            cur_height++;
        }
    }
    return cur_height;
}

int main() {
    vector athletes;
    int a = 0, b = 0;
    while(std::cin >> a >> b) athletes.add(a, b);
    std::cout << max_height(athletes) << std::endl;
    return 0;
}