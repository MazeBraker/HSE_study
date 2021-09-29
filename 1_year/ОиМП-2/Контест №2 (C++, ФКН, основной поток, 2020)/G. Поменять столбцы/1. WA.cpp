#include<iostream>
#include<ctime>

using namespace std;

int main() {
    // Ввод
    int n, m, k;
    // n и m - количество строк и столбцов на поле, а также количество мин на поле k
    cin >> n >> m >> k;
    string arr[102], r = "";
    // Заполняем нулями
    for (int j = 0; j < m; ++j) {
        r += '0';
        for (int i = 0; i < n; ++i) {
            arr[i] = r;
        }
    }
    for (int l = 0; l < k; ++l) {
        // ввод k пар координаты мин
        int x, y;
        cin >> x >> y;
        arr[x - 1][y - 1] = '*';
    }
    // Тело проги
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            // если не мина, то
            if (arr[i][j] != '*') {
                // считываем соседей
                int l = 0;
                if (i > 0 && j > 0 && arr[i - 1][j - 1] == '*')   // левый верхний по диаг
                    l++;
                if (i > 0 && arr[i - 1][j] == '*')   // левый
                    l++;
                if (i > 0 && j < m && arr[i - 1][j + 1] == '*')   // правый верхний по диаг
                    l++;
                if (j > 0 && arr[i][j - 1] == '*')
                    l++;
                if (j < m && arr[i][j + 1] == '*')
                    l++;
                if (i < n && j > 0 && arr[i + 1][j - 1] == '*')
                    l++;
                if (i < n && arr[i + 1][j] == '*')
                    l++;
                if (i < n && j < m && arr[i + 1][j + 1] == '*')
                    l++;
                if (l)   // колово мин у 8 соседей
                    arr[i][j] = '0' + l;
            }
    // Вывод
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }
    //  cout << 1.0 * clock() / CLOCKS_PER_SEC;
    return 0;
}
