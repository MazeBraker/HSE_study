#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main() {
    long long n, nowots;
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