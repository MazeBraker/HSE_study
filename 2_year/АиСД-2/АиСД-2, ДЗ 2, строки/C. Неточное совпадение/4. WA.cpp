#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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


int main() {
    std::vector<int> z_str_rev_str1;
    std::string str, str1, str_rev, str1_rev;
    std::cin >> str1 >> str;
    if (str1.size() > str.size()){
        std::cout << 0 <<'\n' << 0;
        return 0;
    }
    str_rev = str;
    reverse(str_rev.begin(), str_rev.end());

    z_str_rev_str1 = ComputeZ_Smart(str_rev, str1);
    reverse(z_str_rev_str1.begin(), z_str_rev_str1.end());

    vector_ans(Str_in_str(str, str1), str, str1, z_str_rev_str1);
    std::cout << ans.size() << '\n';
    if (ans.size() == 0){
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
    Print_z(ComputeZ_Smart(str_rev, str1));
    std::cout << '\n' << str1[2] << " " << str[7];
     */
    return 0;
}