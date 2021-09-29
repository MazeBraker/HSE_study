#include <stdio.h>
#include <stdlib.h>

const char sym[3] = {'r', 'w', 'x'};

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size <= 0) {
        return buf;
    }

    int nsize = 10;
    if (size > nsize) {
        size = nsize;
    }
    for (int i = 0; size != i + 1; ++i) {
        buf[i] = '-';
    }
    
    buf[size - 1] = '\0';
    for (size_t i = 0; size != i + 1; ++i) {
        if (perms & (1 << (9 - i - 1))) {
            buf[i] = sym[i % 3];
        }
    }

    if ((perms & (1 << 11)) && ((perms & (1 << 3)) || (perms & (1 << 0))) && 3 < size) {
        buf[2] = 's';
    }
    if ((perms & (1 << 10)) && (perms & (1 << 0)) && 6 < size) {
        buf[5] = 's';
    }
    if ((perms & (1 << 9)) && (perms & (1 << 0)) && (perms & (1 << 1)) && 9 < size) {
        buf[8] = 't';
    }
    return buf;
}