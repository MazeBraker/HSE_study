#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>

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

std::vector<int> ComputeZ_Smart(const std::string &s, const std::string &str1) {
    std::vector<int> z(s.size());
    auto res = z_function(str1 + "$" + s);
    for (int i = str1.size() + 1; i < res.size(); ++i) {
        z[i - str1.size() - 1] = res[i];
    }
    return z;
}

void Print_z(const std::vector<int> &z) {
    for (int i = 0; i < z.size(); ++i) {
        std::cout << z[i] << ' ';
    }
}

std::string random_string(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
                //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                //"abcdefghijklmnopqrstuvwxyz";
                "abc";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<int> rev_z;
    std::string str, str1, str_rev, str1_rev;

//    str1 = "acbc";
    //          123456789012
    //     cbca$bcbcbabccbbc
    //     1234567890
    //     bcbcbabccbbc
//    str = "cbbccbabcbcb";
//    str1 = "aaaa";
//           1234567
//    str = "Caaabdaaaa";
    std::cin >> str1 >> str;
    //     0321000000
    //     0000001234
    // 1
    // 7
    if (str1.size() > str.size()) {
        std::cout << 0;
        return 0;
    }
    str_rev = str;
    str1_rev = str1;
    reverse(str_rev.begin(), str_rev.end());
    reverse(str1_rev.begin(), str1_rev.end());

//    std::cout << '\n';
//    std::cout << "str size = " << str.size() << " " << " str1 size = " << str1.size();
//    std::cout << '\n' << "Zfunc ";
//    Print_z(ComputeZ_Smart(str, str1));
//    std::cout << '\n' << "Zfuncr";
//     Print_z(ComputeZ_Smart(str_rev, str1_rev));
//    // */
    std::vector<int> foo, foor;
    foo = ComputeZ_Smart(str, str1);
    foor = ComputeZ_Smart(str_rev, str1_rev);
    reverse(foor.begin(), foor.end());
//    Print_z(foor);
//    std::cout <<'\n';
    //std::cout << "MY check"<<'\n';
    std::vector<int > F;
    int w = 0;
    for (int i = 0; i < foo.size(); i++) {
        if (foo[i] == str1.size()) {
            F.push_back(i+1);
            w++;
            //std::cout << i + 1 << " ";
        }
    }
    for (int i = 0; i < foo.size() - str1.size() + 1; i++) {
        if (foo[i] + foor[i + (str1.size() - 1)] == str1.size() - 1) {
            F.push_back(i+1);
            w++;
            //std::cout << i + 1 << " ";
        }
    }
    if (w == 0){
        std::cout << 0;
        return 0;
    }
    std::sort(F.begin(), F.end());
    std::cout << w <<'\n';
    for (int i = 0; i < F.size(); i++) {
        std::cout << F[i] << " ";
    }
    //*/
    return 0;
}