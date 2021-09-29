#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>

struct Edge {
    int v, u;
    int f = 0, c = 0;

    Edge(int v, int u, int f, int c): v(v), u(u), f(f), c(c) {}
};

bool visited[int(1e5)];
int source;
int sink;
std::vector<Edge> edges;
std::vector<int> graph[int(500)];

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

char a[150], b[150];
int sChars[100];

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

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i];
    }
    std::string s;
    std::cin >> s;

    source = 0;
    sink = 499;
    int cnt = 1;
    for (int i = 0; i < n; ++i) {
        int p = cnt++;
        int v = cnt++; //left a[]
        int u = cnt++; //right b[]
        makeEdge(source, p, 1);
        makeEdge(p, v, 1);
        makeEdge(p, u, 1);
        if (sChars[a[i]])
            makeEdge(v, sChars[a[i]], 1);
        if (sChars[b[i]])
            makeEdge(u, sChars[b[i]], 1);
    }
    for (auto i:s) {
        sChars[i] = cnt;
        makeEdge(cnt, sink, 1);
        cnt++;
    }
    int ans = 0;
    while (int d = dfs(source, 1e9)) {
        if (d == 0)
            break;
        ans += d;
    }
    std::cout << (ans == s.size()?"YES":"NO");
    return 0;
}