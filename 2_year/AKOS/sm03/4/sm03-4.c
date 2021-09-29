//partial 1
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
// округление к четному вниз (& ~1)
// из примера fixed_mul(0x26, 0x42, 4) == 0x9d умножаются 2 hex числа,
// результат-> бинарный вид и n битов(справа налево) в двоичном виде стираются

uint32_t fixed_mul(uint32_t a, uint32_t b, int n) {
    // если n == 0, то выполняется умножение с насыщением для 32-битных целых беззнаковых чисел
    if (n == 0) {
        uint32_t result;
        // (умножение с насыщением) из пред задачи
        if (__builtin_mul_overflow(a, b, &result)) {
            return UINT32_MAX;
        } else {
            return result;
        }
    } else {
        // чтобы не выделять отдельный случай на 32, то сразу работаем с 64
        uint64_t result = (uint64_t) a * (uint64_t) b;
        // чтобы не было UB, то сперва на (n-1), а не сразу на n
        result >>= (n - 1);
        result >>= 1;
        // переполнение
        if (result > UINT32_MAX) {
            return UINT32_MAX;
        } else {
            return result;
        }
    }
}