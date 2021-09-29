#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>

const int INF = 1e9 + 1;

std::pair<int,int> t[4*int(2e5)];

std::pair<int,int> combine (std::pair<int,int> a, std::pair<int,int> b) {
    if (a.first > b.first)
        return a;
    if (b.first > a.first)
        return b;
    return std::make_pair (a.first, a.second + b.second);
}

void build (int a[], int v, int tl, int tr) {
    if (tl == tr)
        t[v] = std::make_pair (a[tl], 1);
    else {
        int tm = (tl + tr) / 2;
        build (a, v*2, tl, tm);
        build (a, v*2+1, tm+1, tr);
        t[v] = combine (t[v*2], t[v*2+1]);
    }
}

std::pair<int,int> get_max (int v, int tl, int tr, int l, int r) {
    if (l > r)
        return std::make_pair (-INF, 0);
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine (
            get_max (v*2, tl, tm, l, std::min(r,tm)),
            get_max (v*2+1, tm+1, tr, std::max(l,tm+1), r)
    );
}

void update (int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        t[v] = std::make_pair (new_val, 1);
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update (v*2, tl, tm, pos, new_val);
        else
            update (v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine (t[v*2], t[v*2+1]);
    }
}

int a[int(3e5)];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    build(a, 1, 0, n - 1);
    int q;
    std::cin >> q;
    while (q--) {
        int e, l, r;
        std::cin >> e >> l >> r;
//        std::cout << q << '|' << '\n';
        if (e == 1) {
            std::cout << get_max(1, 0, n - 1, l, r).second << '\n';
        } else {
            update(1, 0, n - 1, l, r);
        }
    }
    return 0;
}
/*
3
1 3 3
1
1 0 1

10
3 3 -2 1 2 -1 -3 1 1 3
10
1 0 8
2 7 3
1 4 8
1 3 3
1 6 9
2 9 1
2 3 1
1 0 4
2 7 3
1 3 5


 * */