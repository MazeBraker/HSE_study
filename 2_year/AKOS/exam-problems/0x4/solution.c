#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


int main() {
    uint64_t res = 0;
    uint32_t count = 0;
    uint32_t num, aln;
    uint32_t align = 0;
    uint64_t all_fields = 0;
    while (scanf("%" SCNu32"%" SCNu32, &num, &aln) == 2) {
        ++count;
        all_fields += num;
        if (aln > align)
            align = aln;
        if (res == 0) {
            res = num;
            continue;
        }

        if (res % aln != 0)
            res = res / aln * aln + aln;
    
        res += num;
    }

    if (count > 1) {
        if (res % align != 0)
            res = res / align * align + align;
    } else if (count == 0) {
        res = 1;
        align = 1;
    }

    printf("%" PRIu64 " %" PRIu64 "\n", res, res-all_fields);
    fprintf(stderr, "count=%" PRIu32 "max_align=%" PRIu32 " all_fields=%" PRIu64 "\n", count, align, all_fields);
    return 0;
}
