#include <iostream>

using namespace std;

// деревья отрезков
// https://proglib.io/p/algoritmy-i-struktury-dannyh-na-c-derevya-otrezkov-2019-10-11

const auto SIZE = 100005;
int arr[SIZE]; // массив чисел
int tree[4 * SIZE]; // память дерева отрезков(сложность)
int n; // // кол-во элементов в массиве

void build_sum_tree(int v, int left, int right) {
    if (left == right - 1) {  // Разбили подотрезок на левого и правого потомка(условие выхода)
        if (left < n) {   // Cледим за границей
            tree[v] = arr[left];
        }
        return; // присвоили значение новой вершине
    }
    // Алгоритм : Делим отрезок пополам и запускаем на левом и правом подотрезках
    int mid = (left + right) / 2;
    build_sum_tree(2 * v + 1, left, mid);  // Сумма левого
    build_sum_tree(2 * v + 2, mid, right);  // Сумма правого
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];  // Незабываем обновить текущую вершину
}

//int64_t
long long int get_sum(int v, int left, int right, int l, int r) {
    if (r <= left || right <= l) {  // 1
        return 0;
    }
    if (l <= left && right <= r) {  // 2
        return tree[v];
    }
    int mid = (left + right) / 2;
    int64_t first_child = get_sum(2 * v + 1, left, mid, l, r);
    int64_t second_child = get_sum(2 * v + 2, mid, right, l, r);
    return first_child + second_child;
}

// Хотим заменить элемент индекс i на x
void change_elem_tree(int v, int left, int right, int i, int x) {
    if (left == right - 1) {
        arr[i] = x;
        tree[v] = x;
        return;
    }
    int mid = (left + right) / 2;
    if (i < mid) {
        change_elem_tree(2 * v + 1, left, mid, i, x);
    } else change_elem_tree(2 * v + 2, mid, right, i, x);
    // Меняем значение в родителе
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

int main() {
    // Магия для быстроты in/out. Дано на семе 198
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    // Создали дерево отрезков
    build_sum_tree(0, 0, n);
    // Число запросов, Тип запроса
    // T_i = X_(2Q - 2), T_j = X_(2Q - 1)

    long long Q, T_i, X_i, left_j, right_j;
    long long SUM = 0;
    // Q - кол-во запросов
    cin >> Q;
    // X_0
    cin >> T_i;
    for (int i = 0; i < Q; ++i) {
        // Запрос // 123
        //L0 = min(X0 mod N, X1 mod N), R0 = max(X0 mod N, X1 mod N);
        // Xi = (11173 ⋅ Xi - 1 + 1) mod 1000000007.
        X_i = (11173 * T_i + 1) % 1000000007;
        // cout << T_i <<" "<< X_i << '\n';
        left_j = min(T_i % n, X_i % n);
        right_j = max(T_i % n, X_i % n);
        T_i = (11173 * X_i + 1) % 1000000007;
        // cout << left_j << " "<< right_j << '\n';
        SUM += get_sum(0, 0, n, left_j, right_j + 1);
    }
    cout << SUM;
}