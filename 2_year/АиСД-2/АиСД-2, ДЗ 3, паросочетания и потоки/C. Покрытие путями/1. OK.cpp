#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>
// Алгоритм Куна нахождения наибольшего паросочетания в двудольном графе
// emaxx

std::vector<int> g[501];
std::vector<int> mt;
std::vector<char> used(501);
std::vector<std::pair<int, int>> edge_num;

bool try_kuhn(int v) {
    if (used[v])
        return false;
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
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int v, u;
        std::cin >> v >> u;
        while (v != 0 && u != 0) {
            g[i].push_back(v - 1);
            g[i + 1].push_back(u - 1);
            break;
        }
    }
    mt.assign(n, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }
    for (size_t i = 0; i < m; ++i) {
        if (mt[i] != -1)
            edge_num.emplace_back(std::make_pair(mt[i] + 1, i + 1));
    }
    std::cout << edge_num.size() << '\n';
    for (auto &edge : edge_num) {
        std::cout << edge.first << ' ' << edge.second << '\n';
    }
    return 0;
}