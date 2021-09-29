// Алгоритм Прима через множества
// https://habr.com/ru/post/104772/ теория
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>

std::vector<int> p;

// Система непересекающихся множеств

// Представителем дерева будем считать его корень.
// Тогда для нахождения этого представителя достаточно
// подняться вверх по родительским ссылкам до тех пор, пока не наткнемся на корень.
int find_set(int x) {
    if (x == p[x]) {
        return x;
    } else {
        return p[x] = find_set(p[x]);
    }
}

// корень для переподвешивания случайным образом — как ни удивительно,
// но такое решение дает на практике скорость,
void unite_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (rand() % 2 == 0) {
        std::swap(x, y);
    }
    p[x] = y;
}

int main() {
    int N, M;
    int A, B, cost_d;
    long long min_sum = 0, roads_num = 0;
    int temp = 0;
    std::cin >> N >> M;

    p.resize(N+1);
    for (int k = 1; k <= N; ++k) {
        p[k] = k;
    }
    std::pair<int, std::pair<int, int>> stroka[M];
    for (int k = 0; k < M; ++k) {
        std::cin >> A >> B >> cost_d;
        stroka[k] = std::make_pair(cost_d, std::make_pair(A, B));
    }

    sort(stroka, stroka + M);
    for (int k = 0; k < M; ++k) {
        A = find_set(stroka[k].second.first);
        B = find_set(stroka[k].second.second);
        if (A != B) {
            min_sum += stroka[k].first;
            if (stroka[k].first != 0) {
                roads_num++;
            }
            temp++;
            unite_set(A, B);
        }
        // все вершины
        if (temp == N - 1) {
            break;
        }
    }
    std::cout << min_sum << " " << roads_num;
    return 0;
}