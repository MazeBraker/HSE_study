#include <iostream>
#include <string>
#include <algorithm>

std::string common_suffix(const std::string &a, const std::string &b) {
    int i, j;
    std::string suf;
    i = a.size() - 1;
    j = b.size() - 1;
    while (i >= 0 && j >= 0) {
        if (a[i] == b[j]) {
            suf += a[i];
            i -= 1;
            j -= 1;
        } else {
            break;
        }
    }
    reverse(suf.begin(), suf.end());
    return suf;
}
/*
int main() {
    std::string a, b;
    std::cin >> a >> b;
    std::cout << common_suffix(a, b);
    return 0;
}*/