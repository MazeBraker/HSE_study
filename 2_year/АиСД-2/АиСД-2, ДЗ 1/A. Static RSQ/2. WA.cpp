#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

void build_sum_tree(long long int &n, std::vector<long long int> &arr,
                    std::vector<long long int> &tree) {
    for (long long int i = n - 1; i <= 2 * n - 2; ++i) {
        tree[i] = arr[i - n + 1];
    }
    for (long long int i = n - 2; i >= 0; --i) {
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

long long get_sum(long long int v, long long int left, long long int right,
                  long long int l, long long int r, std::vector<long long int> &tree) {
    if (r <= left || right <= l) { // 1 случай
        return 0;
    }
    if (l >= left && right >= r) { // 2 случай
        return tree[v];
    }
    int mid = (l + r) / 2;
    return get_sum(2 * v + 1, left, right, l, mid, tree)
           + get_sum(2 * v + 2, left, right, mid, r, tree);
}

// обновление сверху 18-19 слайд
void change_elem_tree(long long int i, long long int x, long long int N, std::vector<long long int> &tree) {
    long long int v = i + N - 1;
    // обозначаем любой четный элемент за 1, следовательно их количество это сумма 1
    tree[v] = x;
    while (v > 0) {
        v = (v - 1) / 2;
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }
}

int main() {
    // Магия для быстроты in/out. Дано на семе 198
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long int n, old;
    std::cin >> n;
    // Дополняем размер до степени двойки.СОБАКА
    long long int size_2 = 1 << int(ceil(log2(n)));
    // Заводим массив и дерево
    std::vector<long long int> arr(size_2), tree(size_2 * 2 - 1);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    old = n;
    n = size_2;
    build_sum_tree(n, arr, tree);

    long long int q;
    long long int left, right;
    long long int SUM = 0, T_i, X_i;
    std::cin >> q;
    std::cin >> T_i;
    for (long long int i = 0; i < q; ++i) {
        // Запрос // 123
        //L0 = min(X0 mod N, X1 mod N), R0 = max(X0 mod N, X1 mod N);
        // Xi = (11173 ⋅ Xi - 1 + 1) mod 1000000007.
        X_i = (11173 * T_i + 1) % 1000000007;
        //std::cout << T_i <<" "<< X_i << '\n';
        left = std::min(T_i % old, X_i % old);
        right = std::max(T_i % old, X_i % old);
        T_i = (11173 * X_i + 1) % 1000000007;
        //std::cout << left << " "<< right << '\n';
        SUM += get_sum(0, left, right + 1, 0, n, tree);
    }
    std::cout << SUM % 1000000007;
    return 0;
}