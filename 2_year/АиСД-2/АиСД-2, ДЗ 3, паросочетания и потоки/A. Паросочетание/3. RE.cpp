#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>
#include <cstring>
#include <map>

// максимальный поток с дороботками
struct Edge {
    // first > second
    int first, second;
    int f = 0, c = 0;

    Edge(int v, int u, int f, int c) : first(v), second(u), f(f), c(c) {}
};

bool visited[int(400500)];
int source;
int sink;
std::vector<Edge> edges;
std::vector<int> graph[int(400500)];

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

char a[150], b[150];
std::vector<int> sChars[500];

int makeEdge(int v, int u, int c) {
    auto vu = Edge(v, u, 0, c);
    auto uv = Edge(u, v, 0, 0);
    int vui = edges.size();
    edges.push_back(vu);
    int uvi = edges.size();
    edges.push_back(uv);
    graph[v].push_back(vui);
    graph[u].push_back(uvi);
    return vui;
}

std::map<int, int> iv;

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
    edges.reserve(4*n);

    source = 0;
    sink = 1999;
    int cnt = 1;
    for (int i = 0; i < s.size(); ++i) {
        sChars[s[i]].push_back(cnt);
        makeEdge(cnt, sink, 1);
        iv[cnt] = i;
        cnt++;
    }
    std::map<int, int> ic;
    std::vector<int> im;
    for (int i = 0; i < n; ++i) {
        int p = cnt++;
        int v = cnt++; //left a[]
        int u = cnt++; //right b[]
        ic[v] = i + 1;
        ic[u] = -i - 1;
        // 1 буква, поток 1
        makeEdge(source, p, 1);
        makeEdge(p, v, 1);
        // используем 1 стороны карточки, то 2 не доступна
        makeEdge(p, u, 1);
        if (!sChars[a[i]].empty())
            for (auto q:sChars[a[i]]) {
                im.push_back(makeEdge(v, q, 1));
            }
        if (!sChars[b[i]].empty())
            for (auto q:sChars[b[i]]) {
                im.push_back(makeEdge(u, q, 1));
            }
    }
    int ans = 0;
    while (int d = dfs(source, 1e9)) {
        if (d == 0)
            break;
        ans += d;
        std::memset(visited, false, sink + 1);
    }
    if (ans != s.size()) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    std::vector<int> res(s.size());
    int v, u;
    for (auto ei:im) {
        if (edges[ei].f > 0) {
            v = edges[ei].first;
            u = edges[ei].second;
            res[iv[u]] = ic[v];
        }
    }
    for (auto i:res) {
        std::cout << i << ' ';
    }
    return 0;
}