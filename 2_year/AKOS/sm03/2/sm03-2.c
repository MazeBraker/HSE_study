#include <inttypes.h>
#include <stdio.h>
//https://ru.stackoverflow.com/questions/651305/
//16777216 = 2^24
//Порядок (8 бит)   Мантисса (23+1 бита)
int is_float(uint32_t num) {
    for (int i = 0; i != 8; ++i) {
        if (num % 2 == 0) {
            num >>= 1;
        } else {
            break;
        }
    }
    // поместится ли оставшееся в мантиссу (24)
    return (num >> 24) == 0;
}

int main(void) {
    uint32_t num;
    while (scanf("%" SCNu32, &num) != EOF) {
        printf("%d\n", is_float(num));
    }
    return 0;
}