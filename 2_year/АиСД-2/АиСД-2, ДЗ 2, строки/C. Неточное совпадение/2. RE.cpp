#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

std::vector<int> ComputeZ_Smart(const std::string &s) {
    std::vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

void Print(const std::vector<int> &z) {
    for (int i = 0; i < z.size(); ++i) {
        std::cout << z[i] << ' ';
    }
    //std::cout << '\n';
}


int main(){
    std::set <char> Set;
    std::string str;
    int n;
    std::cin >> n;
    std::cin >> str;
    for (int i = 0; i < str.size(); i++){
        Set.insert(str[i]);
    }
    std::cout << Set.size() <<'\n';
    for(auto &i : Set)
        std:: cout << i <<'\n';
    //Print(ComputeZ_Smart(str));
    return 0;
}