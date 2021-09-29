#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

void build_sum_tree(int &n, std::vector<long long> &arr, std::vector<long long> &tree) {
    for (int i = n - 1; i <= 2 * n - 2; ++i) {
        tree[i] = arr[i - n + 1];
    }
    for (int i = n - 2; i >= 0; --i) {
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

long long get_sum(int v, int left, int right, int l, int r, std::vector<long long> &tree) {
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
void change_elem_tree(int i, long long x, int N, std::vector<long long> &tree) {
    int v = i + N - 1;
    // обозначаем любой четный элемент за 1, следовательно их количество это сумма 1
    tree[v] = abs((x + 1) % 2);
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
    int n;
    std::cin >> n;
    // Дополняем размер до степени двойки.СОБАКА
    int size_2 = 1 << int(ceil(log2(n)));
    // Заводим массив и дерево
    std::vector<long long> arr(size_2), tree(size_2 * 2 - 1);
    int number;
    for (int i = 0; i < n; ++i) {
        std::cin >> number;
        // обозначаем любой четный элемент за 1, следовательно их количество это сумма 1
        arr[i] = abs((number + 1) % 2);
    }
    n = size_2;
    build_sum_tree(n, arr, tree);

    int q, T_i;
    long long left, right;
    std::cin >> q;
    for (int j = 0; j < q; ++j) {
        // Запрос
        std::cin >> T_i;
        if (T_i == 1) {
            std::cin >> left >> right;
            std::cout << get_sum(0, left, right + 1, 0, n, tree) << '\n';
        }
        if (T_i == 2) {
            std::cin >> left >> right;
            change_elem_tree(left, right, n, tree);
        }
    }
    return 0;
}