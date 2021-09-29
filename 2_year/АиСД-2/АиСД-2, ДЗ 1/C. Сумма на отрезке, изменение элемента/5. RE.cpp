#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Простое решение на векторе без дерева отрезков
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long int n, q, l, r;
    cin >> n;
    vector<long long int> a(1000000);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> q;
    int s;
    for (int j = 0; j < q; ++j) {
        cin >> s;
        // cумма
        if (s == 1) {
            cin >> l >> r;
            int sum = 0;
            for (int i = l; i <= r; ++i)
                sum += a[i];
            cout << sum << '\n';
        }
            // присвоение значения x всем элементам отрезка
        else if (s == 2) {
            cin >> l >> r;
            //for(int i = c1 - 1; i < c2; ++i)
            a[l] = r;
        }
    }
    return 0;
}