#include <iostream>

int main() {
    int N, K, M, s1, s2 = 0;
    std::cin >> N >> K >> M;
    while (N >= K && K >= M) {
        //вес металла больше заготовки//
        s1 = N / K;
        //колово заготовок//
        s2 += s1 * (K / M);
        //колово деталей//
        N -= s1 * (K / M) * M;
        //ост металлa//
    }
    std::cout << s2;
    return 0;
}
