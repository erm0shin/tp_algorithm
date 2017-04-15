/*
Во всех задачах данного раздела необходимо реализовать и использовать ​ локальную
пирамидальную сортировку ​ (без использования дополнительной памяти). Общее время работы
алгоритма O(n log n).
3_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли собраться
вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не
исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество
современников. В день 18летия человек уже может принимать участие в собраниях, а в день
80летия и в день смерти уже не может.
Замечание.​ Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях
принимать участие в собраниях он не мог.
 */

#include <iostream>
#include <vector>

typedef struct date {
    int day;
    int month;
    int year;
    date(): day(0), month(0), year(0) {};
    date(int _day, int _month, int _year): day(_day), month(_month), year(_year) {};
    date(const struct date &_date) { day = _date.day; month = _date.month; year = _date.year; }
} Date;

bool greater(const Date &date1, const Date &date2) {
    if (date1.year > date2.year) return true;
    if (date1.year < date2.year) return false;
    if (date1.month > date2.month) return true;
    if (date1.month < date2.month) return false;
    return date1.day > date2.day;
}

/*bool equiv(Date date1, Date date2) {
    return (date1.year == date2.year) &&
            (date1.month == date2.month) &&
            (date1.day == date2.day);
}*/

void dec(Date &date) {
    if (date.day == 1) {
        if (date.month == 1) {
            date.year--;
            date.month = 12;
            date.day = 30;
        }
        else {
            date.month--;
            date.day = 30;
        }
    }
    else
        date.day--;
}

bool analysis(Date &birth, Date &death) {
    Date tmp(birth.day, birth.month, birth.year + 18);
    //если человек не дожил до 18 или умер в день 18-летия
    //то он не может принимать участие в собраниях
    if (!greater(death, tmp)) return false;
    //"сместим" дату рождения человека до дня 18-летия
    //(это первый день, когда он мог принять участие в собраниях)
    birth.year += 18;

    tmp.year += 62;
    //если человек прожил больше 80 лет
    //то "обрежем" его дату смерти до дня 80-летия
    if (greater(death, tmp)) {
        death.year = tmp.year;
        death.month = tmp.month;
        death.day = tmp.day;
    }

    //любой человек не может принимать участие в собраниях в день смерти
    //поэтому "обрежем" его дату смерти до дня накануне смерти
    dec(death);
    return true;
}

typedef struct point {
    Date date;
    int indicator;
    point(): date(), indicator(0) {};
    point(Date _date, int _indicator): date(_date), indicator(_indicator) {};
    point(const struct point &_point) { date = _point.date; indicator = _point.indicator; }
} Point;

bool greater_point(const Point &p1, const Point &p2) {
    return greater(p1.date, p2.date);
}

// Проталкивание элемента вниз
template <class T>
void SiftDown(T *arr, int size, int i, bool (comparer)(const T&, const T&)) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
    int largest = i;
    /*if (left < arr.size() && arr[left] > arr[i]) largest = left;
    if (right < arr.size() && arr[right] > arr[largest]) largest = right;*/
    if (left < size && comparer(arr[left], arr[i])) largest = left;
    if (right < size && comparer(arr[right], arr[largest])) largest = right;
// Если больший сын есть, то проталкиваем корень в него.
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        SiftDown(arr, size, largest, comparer);
    }
}

// Построение кучи.
template <class T>
void BuildHeap(T *arr, int size, bool (comparer)(const T&, const T&)) {
//    for (int i = arr.size() / 2 - 1; i >=0; i--) {
//        SiftDown(arr, arr.size(), i, comparer);
//    }
    for (int i = size / 2 - 1; i >=0; i--) {
        SiftDown(arr, size, i, comparer);
    }
}

template <class T>
void HeapSort(T *arr, int heapSize, bool (comparer)(const T&, const T&)) {
//    int heapSize = arr.size();
    BuildHeap(arr, heapSize, comparer);
    while (heapSize > 1) {
        std::swap(arr[0], arr[heapSize - 1] );
        heapSize--;
        SiftDown(arr, heapSize, 0, comparer);
    }
}

int find_max_sum(Point *arr, int size) {
    int result = 0, cur_max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].indicator > 0) cur_max++;
        else cur_max--;
        if (cur_max > result) result = cur_max;
    }
    return result;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Point> array;
    for (int i = 0; i < n; i++) {
        int day = 0, month = 0, year = 0;
        std::cin >> day >> month >> year;
        Date birth(day, month, year);
        std::cin >> day >> month >> year;
        Date death(day, month, year);
        if (analysis(birth, death)) {
            Point p1(birth, 1), p2(death, -1);
            array.push_back(p1);
            array.push_back(p2);
        }
    }
    HeapSort(&array[0], array.size(), greater_point);
    std::cout << find_max_sum(&array[0], array.size());
    return 0;
}