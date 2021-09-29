#include <iostream>
#include <string>
#include <algorithm>
#include <set>


using namespace std;

int main() {
    set<int> list;
    int e;
    while (cin >> e) {
        if (list.find(e) == list.end()) {
            cout << "NO" << "\n";
            list.insert(e);
        } else {
            cout << "YES" << "\n";
        }
        if (cin.get() == '\n') {
            return 0;
        }
    }
    return 0;
}