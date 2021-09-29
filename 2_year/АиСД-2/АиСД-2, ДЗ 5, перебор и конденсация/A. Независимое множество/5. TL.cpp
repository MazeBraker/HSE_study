#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define ll long long

using namespace std;

// 01111
// 10000
// 10000
// 10000

// 1 - 50
// 011011000000000
//
//

int g[100][100];
ll gm[100];
bool used[100];
//vector<int> rg[100];
int n;

bool checkIn(ll mask, int index) {
    return ((mask>>index)&1) == 1;
}
// ухйня
int count(ll i) {
    i = i - ((i >> 1) & 0x5555555555555555);
    i = (i & 0x3333333333333333) + ((i >> 2) & 0x3333333333333333);
    return (((i + (i >> 4)) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
}

bool bfs(int v, int k) {
    set<ll> cur;
    cur.insert(1<<v);
    while (!cur.empty()) {
        ll m = *cur.begin();
        if (count(m) == k) {
            return true;
        }
        cur.erase(m);
        for (int i = 1; i <= n; ++i) {
            if (count((gm[i]&m)) == count(m) && !used[i]) {
                cur.insert(m^(1<<i));
            }
        }
    }
    return false;
}

int main() {
    int k, m;
    cin >> n >> k >> m;
    for (int i = 1; i <= n; ++i) {
        g[i][i] = -1;
    }
    for (size_t i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v][u] = g[u][v] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (g[i][j] == 0) {
//                rg[i].push_back(j);
//                rg[j].push_back(i);
                gm[i] |= 1<<j;
                gm[j] |= 1<<i;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i] && bfs(i, k)) {
            cout << "YES";
            return 0;
        }
        used[i] = true;
    }
    cout << "NO";
}