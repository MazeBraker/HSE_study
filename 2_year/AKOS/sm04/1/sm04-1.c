#include <stdio.h>
#include <string.h>

int mystrcmp(const char *str1, const char *str2) {
    const unsigned char *str_1 = (const unsigned char *) str1;
    const unsigned char *str_2 = (const unsigned char *) str2;
    while (*str_1 && *str_2) {
        if (*str_1 > *str_2)
            return 1;
        if (*str_1 < *str_2)
            return -1;
        str_1++;
        str_2++;
    }
    // если начало совпало, но одна строка закончилась, а вторая еще есть
    if (*str_1)
        return 1;
    if (*str_2)
        return -1;
    // равны
    return 0;
}
/*
int main() {
        printf("%d\n", mystrcmp("", ""));
        printf("%d\n", strcmp("", ""));
        printf("\n");
        printf("%d\n", mystrcmp("b", "a"));
        printf("%d\n", strcmp("b", "a"));
        printf("\n");
        printf("%d\n", mystrcmp("abc", "abca"));
        printf("%d\n", strcmp("abc", "abca"));
        printf("\n");
        printf("%d\n", mystrcmp("ab", "acdf"));
        printf("%d\n", strcmp("ab", "acdf"));

    return 0;
}*/