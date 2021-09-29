#include <stdio.h>
#include <stdlib.h>

struct BSearchResult {
    size_t low;
    size_t high;
    int result;
};

struct BSearchResult bsearch2(const void *key, const void *base,
                              size_t nmemb, size_t size,
                              int (*compar)(const void *p1, const void *p2, void *user),
                              void *user) {
    struct BSearchResult res;

    res.low = 0;
    res.high = 0;
    res.result = 0;

    int l1 = 0;
    int h1 = nmemb;
    int ans = 0;
    size_t mid;

    while (l1 < h1) {
        mid = l1 + (h1 - l1) / 2;
        ans = (*compar)(key, base + size * mid, user);

        if (ans) {
            if (ans < 0) {
                h1 = mid;
            } else {
                l1 = mid + 1;
            }
        } else {
            res.result = 1;
            h1 = mid;
        }
    }
    ans = 0;
    res.low = l1;

    int l2 = 0;
    int h2 = nmemb;
    while (l2 < h2) {
        mid = l2 + (h2 - l2) / 2;
        ans = (*compar)(key, base + mid * size, user);
        if (ans >= 0) {
            l2 = mid + 1;
        } else {
            h2 = mid;
        }
    }
    res.high = l2;
    return res;
}