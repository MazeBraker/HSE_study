#include <iostream>
#include <map>
#include <utility>
#include <math.h>
#include <string>
#include <queue>

using namespace std;

int main() {
    int n;
    string name, k;
    deque<string> ans;
    map<string, string> ots;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> name >> k;
        if (k == "top") {
            ans.push_front(name);
        }
        if (k == "bottom") {
            ans.push_back(name);
        }
    }
    int m, nom;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> nom;
        cout << ans[nom - 1] << "\n";
    }

    return 0;
}