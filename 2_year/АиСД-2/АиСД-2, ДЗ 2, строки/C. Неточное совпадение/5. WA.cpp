#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>

// Костыли на Z функции
int count = 0;
std::vector<int> ans;

std::vector<int> ComputeZ_Smart(const std::string &s, const std::string &str1) {
    std::vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < s.size() && s[i + z[i]] == str1[z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

void Print_z(const std::vector<int> &z) {
    for (int i = 0; i < z.size(); ++i) {
        std::cout << z[i] << ' ';
    }
    //std::cout << '\n';
}

std::vector<int> Str_in_str(const std::string &s, const std::string &s1) {
    std::vector<int> z(s.size() + s1.size());
    int l = 0, r = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < s.size() && s[i + z[i]] == s1[z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

void
vector_ans(const std::vector<int> &z, const std::string &str, const std::string &str1, const std::vector<int> &rev_z) {
    for (int i = 0; i < str.size() - str1.size() + 1; ++i) {
        if (z[i] == str1.size()) { // match without mistakes
            ans.push_back(i + 1);
        } else if (z[i] < str1.size()) {
            if (rev_z[i + str1.size() - 1] + z[i] == str1.size() - 1)
                ans.push_back(i + 1); // submatch with one mistake.
        } /*else if (z[i] < str1.size() - 1 && (z[i + 1] >= str1.size() - 1) && str1[1] == str[i + 1]) {
            // if ( i == 6) std::cout << "YES";
            ans.push_back(i + 1);
            count = i;
        } else if (z[i] >= str1.size() - 1) {
            ans.push_back(i + 1);
            count = i;
        } else if (z[i] > 0 && z[count] > 0 && i - count >= str1.size() - 1) {
            ans.push_back(i + 1);
        }*/
    }
    //std::cout << '\n';
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
    std::vector<int> rev_z;
    std::string str, str1, str_rev, str1_rev;
    /*
    srand(time(NULL));
    int len = rand() % 5 + 1;
    int len1 = rand() % 5 + 1;
    std::cout << "len = " << len << '\n' << "len1 = " << len1 << '\n';
    srand(time(NULL));
    str1 = random_string(len);
    str = random_string(len1);
    std::cout << "str1 = " << str1 << '\n';
    std::cout << "str = " << str << '\n';
    */

    std::cin >> str1 >> str;
    //str1 = "aaa"; str = "aaaa";
    if (str1.size() > str.size()) {
        std::cout << 0 << '\n' << 0;
        return 0;
    }
    str_rev = str;
    str1_rev = str1;
    reverse(str_rev.begin(), str_rev.end());
    reverse(str1_rev.begin(), str1_rev.end());

    rev_z = ComputeZ_Smart(str_rev, str1_rev);
    reverse(rev_z.begin(), rev_z.end());

    vector_ans(Str_in_str(str, str1), str, str1, rev_z);
    std::cout << ans.size() << '\n';
    if (ans.size() == 0) {
        std::cout << 0;
    }
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " ";
    }
     /*
    std::cout << '\n';
    std::cout << "str size = " << str.size() << " " << " str1 size = " << str1.size();
    std::cout << '\n' << "Zfunc ";
    Print_z(ComputeZ_Smart(str, str1));
    std::cout << '\n';
    Print_z(ComputeZ_Smart(str_rev, str1_rev));
    //std::cout << '\n' << str1[2] << " " << str[7];
     */
    return 0;
}