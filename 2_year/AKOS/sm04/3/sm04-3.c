#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//https://habr.com/ru/post/324642/ про errno
//https://stackoverflow.com/questions/31744305/bit-shifting-with-unsigned-long-type-produces-wrong-results
// про 1ULl
// if (!(numb & ~((1ULL << X) - 1)))
// X = 7,15,31
int main(int argc, char const *argv[]) {
    char *end = 0;

    for (int i = 1; i < argc; ++i) {
        errno = 0;
        // строка в число
        int64_t numb = strtol(argv[i], &end, 10);

        if (!*argv[i] || *end || errno)
            printf("-1\n");
        else if ((int8_t) numb == numb)
            printf("1\n");
        else if ((int16_t) numb == numb)
            printf("2\n");
        else if ((int32_t) numb == numb)
            printf("4\n");
        else printf("-1\n");
    }
    return 0;
}