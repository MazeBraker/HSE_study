#include <iostream>

using namespace std;

int main() {
    int d, h, m, t;
    cin >> d >> h >> m;
    int nowd = d;
    t = h * 60 + m;
    int n, temp = 10080;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int d1, h1, m1, t1;
        cin >> d1 >> h1 >> m1;
        t1 = h1 * 60 + m1;
        if (d1 == 0) {
            if (t1 > t) {
                d1 = d;
                if (temp > t1 - t) {
                    temp = t1 - t;
                    d = d1;
                    h = h1;
                    m = m1;
                }
            } else {
                if (temp > 24 * 60 - t1 + t) {
                    temp = 24 * 60 - t1 + t;
                    d = nowd + 1;
                    h = h1;
                    m = m1;
                }
            }
        } else {
            if (t1 + 24 * d1 * 60 < t + 24 * d * 60) {
                if (temp > (-(t1 + 24 * d1 * 60 + 7 * 24 * 60) + t + 24 * d * 60 + 7 * 24 + 60)) {
                    temp = t1 + 24 * d1 * 60 + 7 * 24 * 60;
                    d = d1;
                    h = h1;
                    m = m1;
                }
            } else {
                if (temp > t1 + 24 * d1 * 60 + 7 * 24 * 60) {
                    temp = t1 + 24 * d1 * 60 + 7 * 24 * 60;
                    d = d1;
                    h = h1;
                    m = m1;
                }
            }
        }
    }
    if (d % 8 == 0) {
        cout << (d + 1) % 8 << " " << h << " " << m;
    } else {
        cout << d % 8 << " " << h << " " << m;
    }
    return 0;
}