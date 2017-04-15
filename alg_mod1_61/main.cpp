/*
Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
пирамиду.
Формат входных данных:
На вход подается количество кубиков N.
Формат выходных данных:
Вывести число различных пирамид из N кубиков.
6_1.​ ​ Высокая пирамида. ​ Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
N ​ ≤ 200.
*/

#include <iostream>

long long pyramid( long long all, long long basis, long long** answers ) {
    if( all < 0  || basis < 0) return 0;

    if( answers[all][basis] != 0 ) return answers[all][basis];

    if(( basis == 1 ) || ( all == 1 )) return 1;

    answers[all][basis] =  pyramid(all - basis, basis, answers) + pyramid(all, basis - 1, answers);

    return answers[all][basis];
}

long long get_variants( long long all, long long basis, long long** answers ) {
    answers = new long long*[all + 1];
    for( long long i = 0; i < all + 1; i++ ) {
        answers[i] = new long long[all + 1];
        for( long long j = 0; j < all + 1; j++) {
            answers[i][j] = 0;
        }
    }
    long long result = pyramid( all, basis, answers );
    for( long long i = 0; i <= all; i++ ) delete [] answers[i];
    delete [] answers;
    return result;
}

int main() {
    long long n = 0;
    std::cin >> n;
    long long** answers;
    std::cout << get_variants( n, n, answers ) << std::endl;
    return 0;
}