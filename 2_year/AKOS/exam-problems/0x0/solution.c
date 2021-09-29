/* -*- mode: c; c-basic-offset: 4 -*- */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b;
    while (scanf("%d%d", &a, &b) == 2) {
        if (a < 0 || a >= 1000000000) abort();
        if (b < 0 || b >= 1000000000) abort();

        if (a >= 500000000) a -= 1000000000;
        if (b >= 500000000) b -= 1000000000;

        int c = a - b;
        if (c < -500000000 || c > 499999999) {
            c = -1;
        } else if (c < 0) {
            c += 1000000000;
        }
        printf("%d\n", c);
    }
}
