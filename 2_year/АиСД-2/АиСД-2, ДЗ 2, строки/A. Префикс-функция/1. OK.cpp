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

std::vector<int> z_function(std::string s) {
    int n = (int) s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
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
    /*
    srand(time(NULL));
    int l = rand() % 10 + 1;
    int len1 = rand() % 20 + 3;
    std::cout << "len = " << l << '\n' << "len1 = " << l << '\n';
    srand(time(NULL));
    //str1 = random_string(len);
    std::string s = random_string(len1);
    std::cout << "str1 = " << s << '\n';
    //std::cout << "str = " << str << '\n';
     */
    int l;
    std::string s;
    std::cin >> l;
    std::cin >> s;
    int n = s.size();
    std::set<char> a;
    if (n <= l) {
        std::cout << 1 << '\n' << s;
        return 0;
    }
    for (auto i:s) {
        a.insert(i);
    }
    if (a.size() == 1) {
        std::cout << 1 << '\n' << s[0];
        return 0;
    }
    if (a.size() == 2) {
        std::cout << 2 << '\n' << (*a.begin()) << '\n' << (*(++a.begin()));
        return 0;
    }
    // abcabcabcabc
    // 2
    std::string word1;
    auto z1 = ComputeZ_Smart(s, s);
    for (int i = 0; i < l; ++i) {
        word1.push_back(s[i]);
        int word1len = word1.size();
        int mn = 1e9;
        int res = -1;
        int left = 1e9;
        // 3
        // abcbca
        for (int j = 0; j < z1.size(); ++j) {
            if (z1[j] >= word1len) {
                int k = j - 1;
                if (k >= left) {
                    if (mn > k - left + 1) {
                        mn = k - left + 1;
                        res = left;
                    }
                }
                left = j + word1len;
            } else {

            }
        }
        {
            int k = n - 1;
            if (k >= left) {
                if (mn > k - left + 1) {
                    mn = k - left + 1;
                    res = left;
                }
            }
        }

        if (res == -1) {
            std::cout << 1 << '\n' << word1;
            return 0;
        }
        std::string word2 = s.substr(res, mn);
        int word2len = mn;
        if (mn > l) {
            auto z = z_function(word2);

            bool bad = true;
            for (int w = l; w >= l; --w) {
                if (word2.size() % w == 0) {
                    bad = false;
                    int len = w;
                    for (int x = len; x < word2.size(); x += len) {
                        if (z[x] < len) {
                            bad = true;
                            break;
                        }
                    }
                    if (bad)
                        continue;
                    word2 = word2.substr(0, len);
                    word2len = len;
                    break;
                }
            }
            if (bad)
                continue;
        }
        auto z2 = ComputeZ_Smart(word2, s);
        int bad = false;
        for (int j = 0; j < s.size();) {
            if (z1[j] >= word1len) {
                j += word1len;
            } else if (z2[j] >= word2len) {
                j += word2len;
            } else {
                bad = true;
                break;
            }
        }
        if (bad) {
            continue;
        }
        std::cout << "2\n" << word1 << '\n' << word2;
        return 0;
    }
    std::cout << "3\na\nb\nc";
    return 0;
}