#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int main() {
    string str1;
    int d1;
    bool f_yes;
    f_yes = true;
    getline(cin, str1);
    for (int i = 0; i < str1.length(); i++) {
        while (str1[i] == ' ') {
            str1.erase(i, 1);  //  удаляю пробелы
        }
    }
    d1 = str1.length();
    for (int i = 0; i < d1 / 2; i++)
        if (str1[i] != str1[d1 - i - 1])
            f_yes = false;
    if (f_yes)
        cout << "yes";
    else
        cout << "no";

    return 0;
}
//   argentina manit     negra