#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char n[128];
    cin >> n;
    int f;
    f = strlen(n);
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    for (int i = 0; i <= f; i++) {
        if (33 > n[i] || n[i] > 127) d++;
        if (33 <= n[i] && n[i] <= 127) e++;
        if (n[i] >= '0' && n[i] <= '9') a++;
        if (n[i] >= 'a' && n[i] <= 'z') b++;
        if (n[i] >= 'A' && n[i] <= 'Z') c++;
    }

    if (d == 0 && f >= 8 && f <= 14 && (a + b + c + e >= 9))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}