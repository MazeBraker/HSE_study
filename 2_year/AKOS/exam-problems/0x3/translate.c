
#include <stdint.h>

uint32_t translate(uint32_t *table, uint32_t vaddr)
{
    uint32_t *t2 = (uint32_t*) (uintptr_t)table[vaddr >> 24];
    if (!t2) return 0;
    if (!t2[(vaddr >> 14) & 0x3ff]) return 0;
    return t2[(vaddr >> 14) & 0x3ff] | (vaddr & 0x3fff);
}

