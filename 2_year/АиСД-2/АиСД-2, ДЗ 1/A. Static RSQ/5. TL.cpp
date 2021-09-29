#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long int n, result = 0, q;
    std::cin >> n;
    std::vector<long long int> arr(2 * n), MAX(n * 2);
    // Вектор всех вводимых чисел
    for (long long int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    // Вектор всех максимумов на подотрезках 0,1 0,2 ... 0,n

    long long int X;
    std::cin >> q;
    std::cin >> X;
    // всего X : 2q - 1
    std::vector<long long int> arr_xi(2 * q);
    arr_xi[0] = X;
    // Вектор всех X_i
    for (int i = 1; i < 2 * q; ++i) {
        arr_xi[i] = (11173 * arr_xi[i - 1] + 1) % 1000000007;
    }
    long long int left, right;
    // Идем с шагом 2. Сумма подотрезка это разность трезков (лекция)
    for (int i = 1; i < arr_xi.size() + 1; i += 2) {
        // Запрос // 123
        //L0 = min(X0 mod N, X1 mod N), R0 = max(X0 mod N, X1 mod N);
        // Xi = (11173 ⋅ Xi - 1 + 1) mod 1000000007.
        //std::cout << arr_xi[i - 1] <<" "<< arr_xi[i] << '\n';
        left = std::min(arr_xi[i - 1] % n, arr_xi[i] % n);
        right = std::max(arr_xi[i - 1] % n, arr_xi[i] % n);
        auto start = arr.begin() + (left);
        //advance( start, j-1 );
        auto end = arr.begin() + (right + 1);
        //advance( end, k-1 );
        auto location = max_element(start, end);
        //std::cout << *location << "";
        //std::cout << left << " " << right << '\n';
        //std::cout << *location << " ";
        result += *location % 1000000007;
    }
    std::cout << result % 1000000007;
}