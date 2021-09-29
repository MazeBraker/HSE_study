#include <iostream>

// Алг Прим
int main() {
    int N, M;
    int A, B, cost_d, min_sum = 0;
    int temp, roads_num = 0;
    std::cin >> N >> M;

    int stroka[6002][3], V_num[102];
    //Заполнили матрицу смежности
    for (int k = 0; k < M; ++k) {
        std::cin >> stroka[k][0] >> stroka[k][1] >> stroka[k][2];
    }
    //Забили все вершины
    for (int i = 1; i <= N; ++i) {
        V_num[i] = i;
    }

    for (int i = 0; i < N - 1; ++i) {
        cost_d = 30002;
        for (int f = 0; f < M; ++f) {
            if (V_num[stroka[f][0]] != V_num[stroka[f][1]]) {
                if (stroka[f][2] < cost_d) {
                    cost_d = stroka[f][2];
                    if (cost_d == 0){
                        roads_num--;
                    }
                    //std::cout << cost_d;
                    temp = f;
                }
            }
        }
        min_sum += cost_d;
        roads_num++;
        A = V_num[stroka[temp][0]];
        //std::cout << A;
        B = V_num[stroka[temp][1]];
        //std::cout << B;
        for (int j = 1; j <= N; ++j) {
            // нашли путь до одной вершины, забываем ее, ищем до другой
            if (V_num[j] == B) {
                V_num[j] = A;
            }
        }
    }
    std::cout << min_sum << " " << roads_num;
    return 0;
}