#include <stdint.h>
#include <stdio.h>
//https://en.wikipedia.org/wiki/IEEE_754-1985
/*
typedef enum FPClass {
    FFP_ZERO, FFP_DENORMALIZED, FFP_NORMALIZED, FFP_INF, FFP_NAN
} FPClass;
*/
union FP {
    float fvalue;
    struct {
        unsigned m: 23;
        unsigned e: 8;
        unsigned s: 1;
    };
} part;

FPClass fpclassf(float value, int *psign) {
    part.fvalue = value;
    *psign = part.s;
    if (part.m == 0 && part.e == 0) {
        return FFP_ZERO;
    }
    if (part.m > 0 && part.e == 0) {
        return FFP_DENORMALIZED;
    }
    // NaN or INF.
    if (part.e == 0xff) {
        if (part.m == 0) {
            return FFP_INF;
        } else {
            *psign = 0;
            return FFP_NAN;
        }
    }
    // else norma
    return FFP_NORMALIZED;
}