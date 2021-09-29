namespace my_cstring {
    // Вводятся по одной букве, поэтому начинаем сравнивать сразу их
    int strcmp(const unsigned char *s1, const unsigned char *s2) {
        while (*s1 != 0 && *s2 != 0) {
            if (*s1 > *s2) {
                ++s1;
                ++s2;
                // первая строка больше
                return 1;
            } else if (*s1 < *s2) {
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
    const char str1 [] = "";
    const char str2 [] = "  ";
    std::cout << my_cstring::strcmp(str1, str2);
}
*/