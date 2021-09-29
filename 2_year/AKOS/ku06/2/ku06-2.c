#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // file 1, file 2, mod
    int f1 = open(argv[1], O_RDONLY);
    int f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (f1 < 0 || f2 < 0) {
        exit(1);
    } else {
        uint8_t bit, byte = 0;
        int32_t MOD = strtol(argv[3], NULL, 10);
        int numb = read(f1, &byte, 1);
        uint32_t x = 0;
        uint64_t sum = 0;
        while (numb == sizeof(byte)) {
            for (uint32_t i = 1; i < 9; ++i) {
                // то есть бит есть в массиве
                if ((byte & ((uint8_t)1 << (i - 1))) != 0) {
                    bit = 1;
                } else {
                    bit = 0;
                } // $\sum_{i=1}^x i^2 \pmod{MOD}$
                sum = (sum + (i + x) * (i + x) % MOD);
                sum %= MOD;
                if (bit == 1) {
                    write(f2, &sum, sizeof(int)); // записываем во 2 файл
                }
            }
            x += 8; // идем на след число в массиве, сразу через 8 бит(позииий)
            numb = read(f1, &byte, 1);
        }
    }
    close(f1);
    close(f2);
    return 0;
}