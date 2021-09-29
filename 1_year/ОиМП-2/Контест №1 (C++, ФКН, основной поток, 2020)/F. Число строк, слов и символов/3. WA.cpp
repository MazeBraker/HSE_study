#include <iostream>
#include <iomanip>

using namespace std;

// Эта функция печатает первую и вторую строки
// Это заголовок от 1 до end
void zagolovok(int start, int end) {
    // Отступ
    cout << "\t";
    for (int firstrow = start; firstrow <= end; firstrow++) {
        cout << firstrow << "\t";
        // печать заголовка
    }
    cout << endl;
}

int main() {
    int const start = 1;
    int end;
    int div;
    cin >> end >> div;
    //Вложенный цикл будет перебирать строки и столбцы
    for (int i = start; i <= end; i++) {
        // Убирает умножение на 1,тк это заголовок
        if (i == start) {
            zagolovok(start, end);
        }
        // Для столбцов
        for (int j = start; j <= end; j++) {
            //Для строк
            if (j == start) {
                cout << i << "\t";
            }
            // Находим элемент на пересечение i-й строки и j-го столбца
            cout << (i * j) % div << "\t";
        }
        // Заканчиваем,начинаем сначала
        cout << endl;
    }
    return 0;
}