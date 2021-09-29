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

int count(ll i) {
    i = i - ((i >> 1) & 0x5555555555555555);
    i = (i & 0x3333333333333333) + ((i >> 2) & 0x3333333333333333);
    return (((i + (i >> 4)) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
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
        g[v][u] = g[u][v] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (g[i][j] == 0) {
//                rg[i].push_back(j);
//                rg[j].push_back(i);
                gm[i] |= 1ll<<j;
                gm[j] |= 1ll<<i;
                d[i]++;
                d[j]++;
            }
        }
    }
    if (dfs(0, 1, k, 0)) {
        cout << "YES";
        return 0;
    }
    cout << "NO";
}