#include <iostream>

using namespace std;

int main() {
    string str;
    getline(cin, str);
    if (str[str.size() - 1] <= '8') {
        str[str.size() - 1]++;
        //обращаемся к последнему элементу,увеличиваем на 1, тк нет переполнения//
        cout << str;
        return 0;
    }
    if (str[str.size() - 1] == '9') {
        int j = 0;
        while (str[str.size() - 1 - j] == '9')  //увеличиваем разряд//
            j++;
        if (str.size() != j) {
            str[str.size() - 1 - j]++;
            //находим первую с конца не 9,которую увеличиваем на 1//
            for (auto f = 0; f < j; f++)
                //все 9 в конце числа надо заменить на 0//
                str[str.size() - j + f] = '0';
            //если была 9, то заменяем на 0//
        }
        if (str.size() == j) {
            str = '1';
            for (auto f = 0; f < j; f++)
                str += '0';
        }
        cout << str;
        return 0;
    }
}