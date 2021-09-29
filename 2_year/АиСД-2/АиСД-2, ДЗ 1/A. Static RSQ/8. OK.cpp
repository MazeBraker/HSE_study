#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

void build_sum_tree(long long &n, std::vector<long long> &arr, std::vector<long long> &tree) {
    for (int i = n - 1; i <= 2 * n - 2; ++i) {
        tree[i] = arr[i - n + 1];
    }
    for (int i = n - 2; i >= 0; --i) {
        tree[i] = std::max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}

long long get_max(int v, int left, int right, int l, int r, std::vector<long long> &tree) {
    if (r <= left || right <= l) { // 1 случай
        return 0;
    }
    if (l >= left && right >= r) { // 2 случай
        return tree[v];
    }
    int mid = (l + r) / 2;
    return std::max(get_max(2 * v + 1, left, right, l, mid, tree),
                    get_max(2 * v + 2, left, right, mid, r, tree));
}


int main() {
    // Магия для быстроты in/out. Дано на семе 198
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n, old;
    std::cin >> n;
    // Дополняем размер до степени двойки.СОБАКА
    long long size_2 = 1 << int(ceil(log2(n)));
    // Заводим массив и дерево
    std::vector<long long> arr(size_2), tree(size_2 * 2 - 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    old = n;
    n = size_2;
    build_sum_tree(n, arr, tree);

    long long left, right, SUM = 0;
    long long int X, q;
    std::cin >> q;
    std::cin >> X;
    // всего X : 2q - 1
    std::vector<long long int> arr_xi(2 * q);
    arr_xi[0] = X;
    // Вектор всех X_i
    for (int i = 1; i < 2 * q; ++i) {
        arr_xi[i] = (11173 * arr_xi[i - 1] + 1) % 1000000007;
    }

    // Идем с шагом 2. Сумма подотрезка это разность трезков (лекция)
    for (int i = 1; i < arr_xi.size() + 1; i += 2) {
        // Запрос // 123
        //L0 = min(X0 mod N, X1 mod N), R0 = max(X0 mod N, X1 mod N);
        // Xi = (11173 ⋅ Xi - 1 + 1) mod 1000000007.
        //std::cout << arr_xi[i - 1] <<" "<< arr_xi[i] << '\n';
        left = std::min(arr_xi[i - 1] % old, arr_xi[i] % old);
        right = std::max(arr_xi[i - 1] % old, arr_xi[i] % old);
        //std::cout << left << " " << right << '\n';
        SUM += get_max(0, left, right + 1, 0, n, tree) % 1000000007;
    }
    std::cout << SUM % 1000000007;
    return 0;
}