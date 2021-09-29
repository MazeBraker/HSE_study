#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>


int peek[10000][10000];
long long arr[1000005];

// Построение разряженной таблицы
void buildSparseTable(long long arr[], long long n) {
    for (int i = 0; i < n; i++)
        peek[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            peek[i][j] = peek[(peek[i][j - 1] >
                               peek[i + (1 << (j - 1))][j - 1] ? i : i + (1 << (j - 1)))][j - 1];
        }
    }
}

int get_max(int left, int right) {
    int j = (int) log2(right - left + 1);
    if (peek[left][j] < peek[right - (1 << j) + 1][j])
        return peek[right - (1 << j) + 1][j];
    else
        return peek[left][j];
}

int main() {
    // Магия для быстроты in/out. Дано на семе 198
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    srand(time(NULL));
    long long n, old;
    //std::cin >> n;
    n = 1 + rand() % ((100000 + 1) - 0);
    std::cout << n <<"= N" <<'\n';
    // генератор
    for (int i = 0; i < n; ++i) {
        arr[i] = 0 + rand() % ((1000000000 + 1) - 0);
        std::cout << arr[i] <<"= A_i"<<i <<'\n';
    }
    old = n;

    buildSparseTable(arr, n);

    long long left, right, SUM = 0;
    long long int X, q;
    //std::cin >> q;
    q = 1 + rand() % ((10000000 + 1) - 1);
    std::cout << q <<"= Q" <<'\n';
    //std::cin >> X;
    X = 0 + rand() % ((1000000000 + 1) - 0);
    std::cout << X <<"= X" <<'\n';
    // всего X : 2q - 1
    std::vector<long long int> arr_xi(2 * q);
    arr_xi[0] = X;
    // Вектор всех X_i
    for (long long i = 1; i < 2 * q; ++i) {
        arr_xi[i] = (11173 * arr_xi[i - 1] + 1) % 1000000007;
    }

    // Идем с шагом 2. Сумма подотрезка это разность трезков (лекция)
    for (long long i = 1; i < arr_xi.size() + 1; i += 2) {
        // Запрос // 123
        //L0 = min(X0 mod N, X1 mod N), R0 = max(X0 mod N, X1 mod N);
        // Xi = (11173 ⋅ Xi - 1 + 1) mod 1000000007.
        //std::cout << arr_xi[i - 1] <<" "<< arr_xi[i] << '\n';
        left = std::min(arr_xi[i - 1] % old, arr_xi[i] % old);
        right = std::max(arr_xi[i - 1] % old, arr_xi[i] % old);
        //std::cout << left << " " << right << '\n';
        //std::cout << get_max(left, right) << '\n';
        SUM += get_max(left, right) % 1000000007;
    }
    std::cout << "SUM = " << SUM % 1000000007;
    return 0;
}