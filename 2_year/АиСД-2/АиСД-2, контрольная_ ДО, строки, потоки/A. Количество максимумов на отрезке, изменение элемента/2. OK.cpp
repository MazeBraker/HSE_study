#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>


// Костыли на Z функции
int count = 0;
std::vector<int> ans;

std::vector<int> z_function (std::string s) {
    int n = (int) s.length();
    std::vector<int> z (n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = std::min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    return z;
}

std::vector<int> ComputeZ_Smart(const std::string &q, const std::string &s) {
    std::vector<int> z(s.size());
    auto res = z_function(q + "$" + s);
    for (int i = q.size() + 1; i < res.size(); ++i) {
        z[i - q.size() - 1] = res[i];
    }
    return z;
}

void Print_z(const std::vector<int> &z) {
    for (int i = 0; i < z.size(); ++i) {
        std::cout << z[i] << ' ';
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string s;
    std::cin >> s;
    auto z = z_function(s);
    for (int i = 1; i < s.size(); ++i) {
        bool bad = false;
        for (int j = i; j < s.size(); j += i) {
            if (z[j] >= i || j + z[j] == s.size()) {
                continue;
            } else {
                bad = true;
                break;
            }
        }
        if (bad)
            continue;
        std::cout << i;
        return 0;
    }
    std::cout << s.size();
    return 0;
}