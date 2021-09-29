#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


int bitcount(STYPE v) {
    int cnt = 0;
    UTYPE q = v;
    while (q) {
        cnt += (int)(q&1u);
        q >>= 1u;
    }
    return cnt;
}