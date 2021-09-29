a#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>
#include <cassert>

using namespace std;

const int N = 1000500;
const int INF = 1e9;
vector<int> g[N];
vector<int> e[N];
vector<int> mt;
vector<char> used;

struct Edge {
    int v, u;
    int f = 0, c = 0;

    Edge(int v, int u, int f, int c): v(v), u(u), f(f), c(c) {}
};

vector<bool> visited;
int source = 0;
int sink = N - 1;
std::vector<Edge> edges;
std::vector<int> graph[N];

int dfs(int v, int f) {
    if (v == sink)
        return f;
    visited[v] = true;
    for (auto i:graph[v]) {
        Edge *vu = &edges[i];
        if (!visited[vu->u] && vu->f < vu->c) {
            int d = dfs(vu->u, std::min(f, vu->c - vu->f));
            if (d > 0) {
                vu->f += d;
                edges[i ^ 1].f -= d;
                return d;
            }
        }
    }
    return 0;
}

void makeEdge(int v, int u, int c) {
    auto vu = Edge(v, u, 0, c);
    auto uv = Edge(u, v, 0, 0);
    int vui = edges.size();
    edges.push_back(vu);
    int uvi = edges.size();
    edges.push_back(uv);
    graph[v].push_back(vui);
    graph[u].push_back(uvi);
}

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 && try_kuhn(mt[to])) {
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
    int n, m, res = 0;
    cin >> n >> m;
    int cnt = 1;
    sink = 4 * n ;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        makeEdge(v, n + u, 1);
    }
    for (int i = 1; i <= n; ++i) {
        makeEdge(source, i, INF);
        makeEdge(n + i, sink, 1);
    }
    visited.assign(sink + 1, false);
    while (int f = dfs(0, INF)) {
        if (!f) {
            break;
        }
        res += f;
        visited.assign(sink + 1, false);
    }
//    mt.assign(n, -1);
//    for (int v = 0; v < n; ++v) {
//        used.assign(n, false);
//        try_kuhn(v);
//    }
//    for (int v = 0; v < n; ++v) {
//        if (mt[v] != -1) {
//            res++;
////            cout << mt[v] << ' ' << v << '\n';
//        }
//    }
    cout << (n - res);
    return 0;
}