// Независимое множество++ 
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define ll long long

using namespace std;

int g[100][100];
ll gm[100];
int d[100];
//vector<int> rg[100];
int n;
//
int count(ll i) {
    int cnt = 0;
    while (i) {
        cnt += i&1;
        i >>= 1;
    }
    return cnt;
}


bool dfs(int i, int l, int k, ll mask) {
    for (int j = i + 1; j <= n - (k - l); j++)  {
        if (d[j] >= k - 1) {
            if (count(mask) == count(mask & gm[j])) {
                if (l < k) {
                    if (dfs(j, l + 1, k, (mask^(1ll<<j)))) {
                        return true;
                    }
                } else {
                    return true;
                }
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
        gm[v] |= 1ll<<u;
        gm[u] |= 1ll<<v;
        d[v]++;
        d[u]++;
    }
    if (dfs(0, 1, k, 0)) {
        cout << "YES";
        return 0;
    }
    cout << "NO";
}