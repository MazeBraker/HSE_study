#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>

using namespace std;

vector<int> g[100500];
vector<int> e[100500];
vector<int> mt;
vector<char> used;

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // (1..n) (n+1...2n)
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        e[v].push_back(u);
        g[v - 1].push_back(u - 1);
    }
    mt.assign(n, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }

    int res = 0;
    for (int v = 0; v < n; ++v) {
        if (mt[v] != -1) {
            res++;
//            cout << mt[v] << ' ' << v << '\n';
        }
    }
    cout << (n - res);
    return 0;
}