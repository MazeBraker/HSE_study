#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<int> x;
    string lst;
    long long n;
    while (cin >> lst) {
        if (lst == "CLEAR") {
            while (!x.empty()) {
                x.pop();
            }
        } else if (lst == "ADD") {
            cin >> n;
            x.push(n);
        } else if (lst == "EXTRACT") {
            if (x.size() == 0) {
                cout << "CANNOT" << endl;
            } else {
                cout << x.top() << endl;
                x.pop();
            }
        }
    }
    return 0;
}