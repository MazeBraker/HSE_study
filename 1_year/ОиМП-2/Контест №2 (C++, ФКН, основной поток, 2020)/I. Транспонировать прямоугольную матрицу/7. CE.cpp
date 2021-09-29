#include<iostream>
#include<ctime>

using namespace std;

int main() {
    int d, m, y;
    cin >> d >> m >> y;
    int f = 0;
    d = d + 2;
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        f = 1;
    }
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10) {
        if (d > 31) {
            d = d % 31;
            m++;
        }
    } else if (m == 2) {
        if (f) {   // високосный
            if (d > 29) {
                d = d % 29;
                m++;
            }
        } else {
            if (d > 28) {   // не вис
                d %= 28;
                m++;
            }
        }
    } else if (m == 12) {
        if (d > 31) {   // новый год
            d %= 31;
            m = 1;
            y++;
        }
    } else {
        if (d > 30) {
            d %= 30;
            m++;
        }
    }
    // в остальных случаях изменяется только день
    cout << d << " " << m << " " << y;
    //   cout << 1.0 * clock() / CLOCKS_PER_SEC;
    return 0;
}