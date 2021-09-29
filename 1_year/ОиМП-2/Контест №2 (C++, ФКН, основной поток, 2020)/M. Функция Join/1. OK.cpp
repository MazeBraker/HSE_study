#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {  // структура студент
    string Name;
    string Surname;
    int Day;
    int Month;
    int Year;
};

int main() {
    int n;
    string name;
    string surname;
    int day;
    int month;
    int year;
    vector<Student> vec;  //вектор "студентов"
    cin >> n;  //считываем число
    for (int i = 0; i < n; i++) {
        cin >> name >> surname >> day >> month >> year;  //считываем данные
        vec.push_back({name, surname, day, month, year});  //и вносим в вектор
    }
    int m;
    cin >> m;  //затем еще число
    string command;
    while (m >= 1) {  //и повторяем m раз
        int key;
        cin >> command >> key;  //считаем команду и ключ
        if (vec.size() < key || key <= 0) {  //если ключ меньше размера вектора или меньше нуля
            cout << "bad request" << "\n";
        } else if (command == "name") {  //если команда - Имя
            cout << vec[key - 1].Name << " " << vec[key - 1].Surname << "\n";  //вывод имени
        } else if (command == "date") {  //если команда - Дата
            cout << vec[key - 1].Day << "." << vec[key - 1].Month << "."
                 << vec[key - 1].Year << "\n";  //вывод даты
        } else {  //в остальных случаях
            cout << "bad request" << "\n";  //иное
        }
        m--;
    }
    return 0;
}