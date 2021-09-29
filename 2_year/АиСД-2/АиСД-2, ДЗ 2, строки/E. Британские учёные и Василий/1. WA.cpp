#include <iostream>
#include <string>
#include <vector>

// Умная реализация по лекции
std::vector<int> ComputePi_Smart(const std::string& s) {
    std::vector<int> pi(s.size());
    for (int i = 1; i < pi.size(); ++i) {
        int now = pi[i - 1];
        while (now > 0 && s[i] != s[now])
            now = pi[now - 1];
        if (s[i] == s[now])
            ++now;
        pi[i] = now;
    }
    return pi;
}

void Print(const std::vector<int>& ans) {
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::string str;
    std::cin >> str;
    Print(ComputePi_Smart(str));
    return 0;
}