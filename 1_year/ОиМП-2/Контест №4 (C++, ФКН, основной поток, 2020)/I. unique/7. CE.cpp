#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> x;
    string lst;    //задаем строку
    long long n;
    while (cin >> lst) {   //читаем ее
        if (lst == "push") {    //выполняем команды, которые встречаем в строке
            cin >> n;
            x.push_back(n);
            cout << "ok" << "\n";
        } else if (lst == "pop") {
            if (x.size() == 0) {
                cout << "error" << "\n";
            } else {
                cout << x.front() << "\n";
                x.pop_front();
            }
        } else if (lst == "front") {
            if (x.size() == 0) {
                cout << "error" << "\n";
            } else {
                cout << x.front() << "\n";
            }
        } else if (lst == "size") {
            cout << x.size() << "\n";
        } else if (lst == "clear") {
            x.clear();
            cout << "ok" << "\n";
        } else if (lst == "exit") {
            cout << "bye" << "\n";
            break;
        }
    }
    return 0;
}