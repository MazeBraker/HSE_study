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
    std::vector<long long int> arr(2 * n), Sum(n * 2);
    // Вектор всех вводимых чисел
    for (long long int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    // Вектор всех сумм на подотрезках 0,1 0,2 ... 0,n
    Sum[0] = 0;
    Sum[1] = arr[0];
    for (int i = 2; i < n + 1; ++i) {
        Sum[i] = Sum[i - 1] + arr[i - 1];
    }

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
        //std::cout << left << " " << right << '\n';
        result += (Sum[right + 1] - Sum[left]) % 1000000007;
    }
    std::cout << result;
}