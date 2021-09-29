#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cmath>
#include <set>
#include <cstring>

// Костыли на Z функции
void ComputeZ_Smart(char *str, int *z) {
    z[0] = 0;
    for (int i = 1, l = 0, r = 0; str[i]; ++i) {
        z[i] = std::min(z[i - l], std::max(0, r - i + 1));
        while (str[z[i]] == str[i + z[i]])
            z[i]++;
            l = i;
            r = i + z[i] - 1;
    }
}

void Print_ans(char *s, int len) {
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
    const int N = 200200;
    char str[N];
    int z_word1[N], z_word2[N];
    int tried[N], now, len;
    bool wrong[N];
    std::cin >> len >> str;

    std::set<char> a;
    
    ComputeZ_Smart(str, z_word1);
    z_word1[0] = len;
    for (int len_word1 = 1; len_word1 <= len; ++len_word1) {
        if (wrong[len_word1]) continue;
        int start = len_word1;
        while (z_word1[start] >= len_word1)
            start += len_word1, wrong[start] = true;
        if (start == strlen(str)) {
            //printf("1\n");
            std::cout << "1\n";
            Print_ans(str, len_word1);
            return 0;
        }
    }
    for (int len_word1 = 1; len_word1 <= len; ++len_word1) {
        if (!wrong[len_word1]) {
            int go = len_word1;
            while (z_word1[go] >= len_word1)
                go += len_word1;
            ComputeZ_Smart(str + go, z_word2 + go);
            z_word2[go] = len, ++now;
            for (int len_word2 = 1; len_word2 <= len; ++len_word2) {
                int pos = go + len_word2;
                while (tried[pos] != now) {
                    tried[pos] = now;
                    if (z_word1[pos] < len_word1) {
                        if (z_word2[pos] >= len_word2)
                            pos += len_word2;
                        else
                            break;
                    } else pos += len_word1;
                }
                if (pos == strlen(str)) {
                    //printf("2\n");
                    std::cout << "2\n";
                    Print_ans(str, len_word1);
                    Print_ans(str + go, len_word2);
                    return 0;
                }
            }
        }
    }
    std::cout << "3\na\nb\nc\n";
    return 0;
}