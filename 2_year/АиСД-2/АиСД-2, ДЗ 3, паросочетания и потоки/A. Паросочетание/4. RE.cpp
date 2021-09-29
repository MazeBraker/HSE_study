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

std::vector<int> g[500];
std::vector<int> mt;
std::vector<char> used;
std::vector<std::pair<int, int>> edge_num;

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
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        while (v != 0) {
            g[i].push_back(v - 1);
            std::cin >> v;
        }
    }
    mt.assign(n, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }

    //int res = 0;
    for (auto i = 0; i < n; ++i) {
        if (mt[i] != -1) {
            edge_num.emplace_back(std::make_pair(mt[i] + 1, i + 1));
//            cout << mt[v] << ' ' << v << '\n';
        }
    }
    std::cout << edge_num.size() << '\n';
    for (auto &edge : edge_num) {
        std::cout << edge.first << ' ' << edge.second << '\n';
    }

    return 0;
}