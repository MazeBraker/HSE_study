#include <iostream>
#include <string>
#include <algorithm>

std::string common_prefix(const std::string &a, const std::string &b) {
    int i, j, k = 0;
    std::string pref;
    int n = 0, m = 0;
    string a, b;
    string s = " ";
    while (s != "/0"){
        a = getline(std::cin, s);
        b = getline(std::cin, s);
        k++;
    }
    for (int f = 0; f <= k; f++) {
        while (i >= n && j >= m) {
            if (a[n] == b[m]) {
                pref += a[n];
                i -= 1;
                j -= 1;
            } else {
                break;
            }
        }
        b = a;
    }

    return pref;
}
