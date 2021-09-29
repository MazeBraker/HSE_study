namespace my_cstring {
    // Вводятся по одной букве, поэтому начинаем сравнивать сразу их
    int strcmp(const char *s1, const char *s2) {
        while (*s1 != 0 && *s2 != 0) {
            unsigned c1 = *s1, c2 = *s2;
            if (c1 > c2) {
                ++s1;
                ++s2;
                // первая строка больше
                return 1;
            } else if (c1 < c2) {
                ++s1;
                ++s2;
                // вторая строка больше
                return -1;
            } else {
                // сравниваем слудующие символы
                ++s1;
                ++s2;
                continue;
            }
        }
        // Если за пределы границы вышли обе строки, при этом они были равны
        if (*s1 == 0 && *s2 == 0) {
            return 0;
        } else {
            return *s2 == 0 ? 1 : -1;
        }
    }
}
/*
#include <iostream>
int main(){
    const char str1 [] = "anc";
    const char str2 [] = "anc";
    std::cout << my_cstring::strcmp(str1, str2);
}
*/