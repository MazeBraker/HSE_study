#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1; //exit(1);
    }
    // POSIX API https://www.opennet.ru/docs/RUS/zlp/005.html
    int file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (file < 0) {
        return 0;
    }
    unsigned short a;
    unsigned char be[2];
    while (scanf("%hu", &a) == 1) {
        // CHAR_BIT - это число битов в char . В наши дни почти все архитектуры используют 8 бит на байт
        // меняем порядок байт для Big-Endian.
        be[0] = a >> CHAR_BIT;
        be[1] = a;
        // Запись в файл: системный вызов write()
        ssize_t cd = write(file, &be, 2);
        ++cd;
    }
    close(file);
    return 0;
}