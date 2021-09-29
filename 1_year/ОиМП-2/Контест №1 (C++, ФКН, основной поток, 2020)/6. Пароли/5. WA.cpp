#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char n[128];
    cin >> n;
    int f;
    f = strlen(n);
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    for (int i = 0; i < f; i++) {
        if (33 > n[i] || n[i] > 127) {
            d++;
        } else if (n[i] >= '0' && n[i] <= '9') {
            a++;
        } else if (n[i] >= 'a' && n[i] <= 'z') {
            b++;
        } else if (n[i] >= 'A' && n[i] <= 'Z') {
            c++;
        } else {
            e++;
        }
    }

    if (d == 0 && f >= 8 && f <= 14 && (a >= 3 || b >= 3 || c >= 3 || e >= 3))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}