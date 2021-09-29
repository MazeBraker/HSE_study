#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int g[100][100];
int used[100];
vector<int> rg[100];
int n;

bool dfs(int v, int k, set<int> &s) {
//    for (auto i:s) {
//        cout << i << ' ';
//    }
//    cout << '\n';
    used[v] = 1;
    if (k == 1) {
        return true;
    }
    s.insert(v);
    for (auto i:rg[v]) {
        if (!used[i] && g[v][i] == 0 && s.find(i) == s.end()) {
            bool bad = false;
            for (auto u:s) {
                if (g[i][u] != 0) {
                    bad = true;
                    break;
                }
            }
            if (!bad && dfs(i, k - 1, s)) {
                return true;
            }
        }
    }
    s.erase(v);
    return false;
}

int main() {
    int k, m;
    cin >> n >> k >> m;
    for (int i = 1; i <= n; ++i) {
        g[i][i] = -1;
    }
    for (size_t i = 1; i <= m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v][u] = g[u][v] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (g[i][j] == 0) {
                rg[i].push_back(j);
                rg[j].push_back(i);
            }
        }
    }
    set<int> c;
    for (int i = 1; i <= n; ++i) {
        if (dfs(i, k, c)) {
            cout << "YES";
            return 0;
        }
        used[i] = 1;
    }
    cout << "NO";
}