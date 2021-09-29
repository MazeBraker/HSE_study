#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Наивная реализация по лекции O(S^2)
// Мы просто для каждой позиции i перебираем ответ для неё
// z[i], начиная с нуля, и до тех пор, пока мы не обнаружим несовпадение или не дойдём до конца строки
/*
std::vector<int> ComputeZ_Stupid(const std::string &s) {
    std::vector<int> z(s.size());
    for (int i = 1; i < z.size(); ++i) {
        //int now = z[i - 1];
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
    }
    return z;
}
*/
// Умная реализация по лекции
// поддерживаем отрезок [l,r], в цикле while увеличиваем r на 1, т.е O(n)
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

int main() {
    std::string str;
    std::cin >> str;
    Print(ComputeZ_Smart(str));
    return 0;
}