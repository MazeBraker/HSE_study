/* -*- mode: c; c-basic-offset: 4 -*- */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned p, q, n;
    scanf("%u%u%u", &p, &q, &n);

    unsigned char *digs = calloc(n + 3, 1);
    digs[0] = '0';
    digs[1] = '.';
    for (unsigned i = 0; i < n; ++i) {
        unsigned dig = (p * 10ULL) / q;
        p = (p * 10ULL) % q;
        digs[i + 2] = '0' + dig;
    }

    // rounding
    int need_inc = 0;
    if ((unsigned long long) p + p == q && (digs[n + 1] % 2) == 1) {
        need_inc = 1;
    } else if ((unsigned long long) p + p > q) {
        need_inc = 1;
    }

    if (need_inc) {
        int i = n + 1;
        while (1) {
            if (digs[i] == '.') {
                digs[0] = '1';
                break;
            } else if (digs[i] < '9') {
                ++digs[i];
                break;
            } else {
                digs[i] = '0';
                --i;
            }
        }
    }

    printf("%s\n", digs);
}
