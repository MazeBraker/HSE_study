#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// деревья отрезков
// https://proglib.io/p/algoritmy-i-struktury-dannyh-na-c-derevya-otrezkov-2019-10-11
// Алгоритм четный элемент по модулю 2 дает 0, поэтому + 1 и выходит 1.Сумма 1 это и есть кол-во четных!
const int SIZE = 100005;
int arr[SIZE]; // массив чисел
int tree[4 * SIZE]; // память дерева отрезков(сложность)
int n; // // кол-во элементов в массиве

void build_sum_tree(int v, int left, int right) {
    if (left == right - 1) {  // Разбили подотрезок на левого и правого потомка(условие выхода)
        tree[v] = abs((arr[left] + 1) % 2);  //добавляем только четный элемент
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
    return get_sum(2 * v + 1, left, mid, l, r) +
           get_sum(2 * v + 2, mid, right, l, r);

}

// Хотим заменить элемент индекс i на x
void change_elem_tree(int v, int left, int right, int i, int x) {
    if (left == right - 1) {
        arr[i] = x;
        tree[v] = abs((arr[left] + 1) % 2); // добавляем только четный элемент
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
    int Q, T_i, left_j, right_j;
    cin >> Q;
    for (int j = 0; j < Q; ++j) {
        // Запрос
        cin >> T_i;
        cin >> left_j >> right_j;
        if (T_i == 1) {
            cout << get_sum(0, 0, n, left_j, right_j + 1) << '\n';
        }
        if (T_i == 2) {
            change_elem_tree(0, 0, n, left_j, right_j);
        }
    }
}