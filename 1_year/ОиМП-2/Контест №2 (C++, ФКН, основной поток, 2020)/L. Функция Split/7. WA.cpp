#include <iostream>
#include <string>
#include <string>

std::string common_suffix(const std::string& a, const std::string& b) {
    int i, j;
    std::string ans, suf;
    j = b.size() - 1;
    i = a.size() - 1;
    int k = 0;
    while (i >= 0 && j >= 0) {
        if (a[i] == b[j]) {
            i -= 1;
            j -= 1;
            suf += a[i];
            k++;
        } else {
            break;
        }
    }
    for (int i = 0; i < suf.size(); ++i) {
        ans.push_back(suf[suf.size() - i - 1]);
    }
}