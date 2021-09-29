#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char n[20];
    cin >> n;
    int f;
    f = strlen(n);
    int a = 0, b = 0, c = 0;
    for (int i = 0; i <= f; i++) {
        if (n[i] >= '0' && n[i] <= '9') a = 1;
        if (n[i] >= 'a' && n[i] <= 'z') b = 1;
        if (n[i] >= 'A' && n[i] <= 'Z') c = 1;
    }

    if (f >= 8 && f <= 14 && a == 1 && b == 1 && c == 1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}