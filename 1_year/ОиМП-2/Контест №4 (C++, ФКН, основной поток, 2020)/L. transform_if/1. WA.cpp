#include <iostream>

using namespace std;
int n;
int a[100002];

int closest(int c) {
    int left = 0;
    int right = n - 1;
    for (int i = 0; i < 100; i++) {
        int mid = (right + left) / 2;
        if (a[mid] > c) {
            right = mid;
        } else {
            left = mid;
        }
    }
    if (left != right) {
        if (abs(a[right] - c) < abs(a[left] - c)) {
            return right;
        } else {
            return left;
        }
    }
    return left;
}

int main() {
    int k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0, c; i < k; i++)
        scanf("%d", &c), cout << a[closest(c)] << "\n";
    return 0;
}
