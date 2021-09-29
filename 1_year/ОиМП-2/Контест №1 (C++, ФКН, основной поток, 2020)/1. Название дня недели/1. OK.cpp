#include <iostream>
#include <string>

using namespace std;

int main() {
    string x, y, z;
    cin >> x;
    int f = 0;
    y.push_back(x[0]);

    for (int i = 1; i < x.size(); ++i) {
        if (x[i] == 'b' || x[i] == 'f' || x[i] == 'p' || x[i] == 'v') {
            y.push_back('1');
        } else if (x[i] == 'c' || x[i] == 'g' || x[i] == 'j' || x[i] == 'k') {
            y.push_back('2');
        } else if (x[i] == 'q' || x[i] == 's' || x[i] == 'x' || x[i] == 'z') {
            y.push_back('2');
        } else if (x[i] == 'd' || x[i] == 't') {
            y.push_back('3');
        } else if (x[i] == 'l') {
            y.push_back('4');
        } else if (x[i] == 'm' || x[i] == 'n') {
            y.push_back('5');
        } else if (x[i] == 'r') {
            y.push_back('6');
        }
    }
    for (int i = 2; i < y.size(); i++) {
        if (y[i - 1] == y[i]) {
            y[i - 1] = '0';
            f++;
        }
    }
    for (int i = 0; i < y.size(); i++) {
        if (y[i] == '0') {
            y.erase(i, 1);
            i--;
        }
    }
    if (y.size() > 4) {
        for (int i = 0; i < 4; i++) {
            z.push_back(y[i]);
        }
    } else {
        for (int i = y.size(); i <= 3; i++) {
            y.push_back('0');
        }
        z = y;
    }
    cout << z;
    return 0;
}