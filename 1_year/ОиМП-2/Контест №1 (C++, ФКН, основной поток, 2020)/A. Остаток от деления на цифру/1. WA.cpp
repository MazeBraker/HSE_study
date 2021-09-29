#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    cout << "\t";
    int i = 0;
    while (i <= 9) {
        cout << i << "\t";
        i++;
    }
    i = 65;
    while (i <= 70) {
        cout << char(i) << "\t";
        i++;
    }
    cout << '\n';
    for (int i = 0; i <= 5; i++) {
        cout << i + 2 << "\t";
        for (int j = 0; j < 16; j++)
            cout << char(32 + (i * 16) + j) << "\t";
        cout << "\n";
    }
    return 0;
}