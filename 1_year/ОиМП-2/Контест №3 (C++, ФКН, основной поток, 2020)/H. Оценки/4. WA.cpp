#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main() {
    int n, nowots = 0;
    cin >> n;
    string name;
    map<string, pair<int, int>> ots;
    for (int i = 1; i <= n; i++) {
        cin >> name >> nowots;
        ots[name].first += nowots;
        ots[name].second++;
        cout << ots[name].first / ots[name].second << "\n";
    }
}