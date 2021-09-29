#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
//подобное на семе199(16.11)

union U{
    float f;
    unsigned u;
    struct {
        unsigned m:23;
        unsigned o:8;
        unsigned s:1;
    } s1;
};//32 bits

int main() {
    union U u;
    while (scanf("%f", &u.f) == 1) {
        printf("%u %u %x\n", u.s1.s, u.s1.o, u.s1.m);
    }
    return 0;
}