#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <random>
#include <cmath>
#include <set>


// Костыли на Z функции


void ComputeZ_Smart(char *s, int *z) {
    z[0] = 0;
    for (int i = 1, l = 0, r = 0; s[i]; ++i) {
        z[i] = std::min(z[i - l], std::max(0, r - i + 1));
        while (s[z[i]] == s[i + z[i]])
            z[i]++, l = i, r = i + z[i] - 1;
    }
}

void print_ans(char *s, int len) {
    for (int i = 0; i < len; ++i)
        std::cout << s[i];
    std::cout << '\n';
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
    std::set<char> Set;
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
    const int N = 200020;
    char s[N];
    int z_word1[N], z_word2[N];
    int old[N], now, len;
    bool wrong[N];
    std::cin >> len;
    std::cin >> s;
    int n = strlen(s);
    std::set<char> a;
    ComputeZ_Smart(s, z_word1);
    z_word1[0] = len;
    //len_word1
    for (int len_word1 = 1; len_word1 <= len; ++len_word1) {
        if (!wrong[len_word1]) {
            int begin = len_word1;
            while (z_word1[begin] >= len_word1)
                begin += len_word1, wrong[begin] = true;
            if (begin == n) {
                std::cout << "1" << '\n';
                print_ans(s, len_word1);
                return 0;
            }
        }
    }
    for (int len_word1 = 1; len_word1 <= len; ++len_word1) {
        if (!wrong[len_word1]) {
            int start = len_word1;
            while (z_word1[start] >= len_word1)
                start += len_word1;
            ComputeZ_Smart(s + start, z_word2 + start);
            z_word2[start] = len, ++now;
            for (int len_word2 = 1; len_word2 <= len; ++len_word2) {
                int pos = start + len_word2;
                while (old[pos] != now) {
                    old[pos] = now;
                    if (z_word1[pos] >= len_word1)
                        pos += len_word1;
                    else if (z_word2[pos] >= len_word2)
                        pos += len_word2;
                    else
                        break;
                }
                /*
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
                }*/
                if (pos != n) continue;
                std::cout << "2" << '\n';
                print_ans(s, len_word1);
                print_ans(s + start, len_word2);
                return 0;
            }
        }
    }
    std::cout << "3\na\nb\nc\n";
    return 0;
}