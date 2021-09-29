#include <iostream>
#include <queue>

using namespace std;

int main() {
    int a, k = 0;
    queue<int> first, second;
    for (int i = 1; i <= 5; i++) {
        cin >> a;
        first.push(a);
    }
    for (int j = 1; j <= 5; j++) {
        cin >> a;
        second.push(a);
    }
    while (!first.empty() && !second.empty()) {
        if (k > 1000000) {
            cout << "botva";
            return 0;
        }
        if (first.front() == 0 && second.front() == 9) {
            first.push(0);
            first.push(9);
        } else {
            if (first.front() == 9 && second.front() == 0) {
                second.push(9);
                second.push(0);
            } else {
                if (second.front() > first.front()) {
                    second.push(first.front());
                    second.push(second.front());
                } else {
                    first.push(first.front());
                    first.push(second.front());
                }
            }
        }
        second.pop();
        first.pop();
        k++;
    }
    if (second.empty()) {
        cout << "first " << k;
    } else {
        cout << "second " << k;
    }


    return 0;
}