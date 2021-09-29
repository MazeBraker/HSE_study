#include<iostream>

using namespace std;

int main() {
    int n, m, k, f, count = 0, now = 0, arr[102][102];
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> f;
            if (f == 0 || f == 1) {
                arr[i][j] = f;
            } else {
                continue;
            }
        }
    }
    cin >> k;
    for (int i = 1; i <= n; i++) {
        count = 0;
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 0) {
                count++;
                if (now < count) {
                    now = count;
                }
                if (now == k) {
                    cout << i;
                    return 0;
                }
            } else {
                count = 0;
            }
        }
    }
    if (now < k) {
        cout << 0;
    }
    return 0;
}