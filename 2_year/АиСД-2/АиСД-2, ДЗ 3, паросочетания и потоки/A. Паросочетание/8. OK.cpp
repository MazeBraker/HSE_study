#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>
#include <cstring>
// modern github

struct Edge {
    int first, second;
    int f = 0, c = 0;

    Edge(int v, int u, int f, int c) : first(v), second(u), f(f), c(c) {}
};

const int INF = 1e9;
std::vector<std::vector<int>> graph;
std::vector<Edge> edges;
std::vector<bool> visited;
int source, sink;


int dfs(int v, int f) {
    if (v == sink)
        return f;
    visited[v] = true;
    for (auto i:graph[v]) {
        Edge *vu = &edges[i];
        if (!visited[vu->second] && vu->f < vu->c) {
            int d = dfs(vu->second, std::min(f, vu->c - vu->f));
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    int max_f = 0, now_f;
    std::cin >> n >> m;
    source = 0;
    sink = n - 1;
    graph.assign(n, std::vector<int>(n, 0));
    for (int i = 0, st, fin, cap; i < m; ++i) {
        std::cin >> --st >> --fin >> cap;
        makeEdge(st, fin, cap);
    }
    visited.assign(n, false);
    while ((now_f = dfs(source, INF)) > 0) {
        visited.assign(n, false);
        //std::memset(visited, false, sink + 1);
        max_f += now_f;
    }
    std::cout << max_f;
    return 0;
}