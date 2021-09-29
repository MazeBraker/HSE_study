#include <stdio.h>

void normalize_path(char *buf) {
    // вообщем тут метод протаскивания, указатель finish ищет все значимые буквы в buf
    // а start дает указатель на пред букву, чтобы в buf по этому указателю заменить ее на след
    // так мы простакиваем все буквы с конца в начало и пропускаем '\'
    // так как мы двигаем finish min через 2 "\", то старт смещаем на 1, чтобы указывать на полезный "\"
    char *start = buf;
    char *finish = buf;
    while (*finish != '\0') {
        while ((*start = *finish)) {
            if (*finish == '/') {
                while (*finish == '/') {
                    finish++;
                }
                start++;
            } else {
                start++;
                finish++;
            }
        }
    }
     *finish = '\0';
}

/*
int main() {
//      ///a/////b
//      a/b/a
//      aa///b/a
    char path[120];
    scanf("%s", path);
    printf("WAS: %s\n", path);
    normalize_path(path);
    printf("BECAME: %s\n", path);
    return 0;
}
*/