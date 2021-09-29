#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>

int imull_overflow(int64_t a, int64_t b, int64_t *res) {
    // нужно определить знак, чтобы понять где переполнение
    int sign_res = 0;
    if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
        sign_res = 1;
    }
    *res = (uint64_t) a * (uint64_t) b;
    // проверяем переполнение
    if (sign_res == 0) {
        if (b == 0) {
            return 0;
        } else if ((b > 0 && a > INT64_MAX / b) || (b < 0 && a < INT64_MAX / b)) {
            //значит не поместились
            return 1;
        }
    } else {
        if ((b > 0 && a < INT64_MIN / b) || (b < 0 && b < INT64_MIN / a)) {
            return 1;
        }
    }
    return 0;
}
/*
int main() {
    int64_t a, b, res;
    scanf("%lld %lld", &a, &b);
    res = (uint64_t)a * (uint64_t)b;
    printf("%lld\n", &res);
    printf("%d\n",__builtin_smulll_overflow(123123, 2131231, &res));
    printf("%lld\n", &res);
    printf("%lld\n", INT64_MIN);
    printf("%lld\n", INT64_MAX);
    printf("%d %d\n", imull_overflow(-1, 0, &res), __builtin_smulll_overflow(-1, 0, &res));
    printf("%d %d\n", imull_overflow(-1, INT64_MIN, &res), __builtin_smulll_overflow(-1, INT64_MIN, &res));
    printf("%d %d\n", imull_overflow(-1, INT64_MAX - 1, &res), __builtin_smulll_overflow(-1, INT64_MAX - 1, &res));
    printf("%d %d\n", imull_overflow(-1, INT64_MIN - 1, &res), __builtin_smulll_overflow(-1, INT64_MIN - 1, &res));
    printf("%d %d\n", imull_overflow(-1, INT64_MAX + 1, &res), __builtin_smulll_overflow(-1, INT64_MAX + 1, &res));
    printf("%d %d\n", imull_overflow(-1, INT64_MIN + 1, &res), __builtin_smulll_overflow(-1, INT64_MIN + 1, &res));
    printf("%d %d\n", imull_overflow(2, INT64_MAX / 2, &res), __builtin_smulll_overflow(2, INT64_MAX / 2, &res));
    printf("%d %d\n", imull_overflow(2, INT64_MIN / 2, &res), __builtin_smulll_overflow(2, INT64_MIN / 2, &res));
    printf("%d %d\n", imull_overflow(-2, INT64_MIN / -2, &res), __builtin_smulll_overflow(-2, INT64_MIN / -2, &res));
    printf("%d %d\n", imull_overflow(2, INT64_MIN / 2, &res), __builtin_smulll_overflow(2, INT64_MIN / 2, &res));
    printf("%d %d\n", imull_overflow(-2, INT64_MIN / -2, &res), __builtin_smulll_overflow(-2, INT64_MIN / -2, &res));
    printf("%d %d\n", imull_overflow(-2, INT64_MAX / -2, &res), __builtin_smulll_overflow(-2, INT64_MAX / -2, &res));
    printf("%d %d\n", imull_overflow(2, INT64_MAX / 2, &res), __builtin_smulll_overflow(2, INT64_MAX / 2, &res));
    printf("%d %d\n", imull_overflow(3, INT64_MAX / 3, &res), __builtin_smulll_overflow(3, INT64_MAX / 3, &res));
    printf("%d %d\n", imull_overflow(3, INT64_MAX / 2, &res), __builtin_smulll_overflow(3, INT64_MAX / 2, &res));
    printf("%d %d\n", imull_overflow(4, INT64_MAX / 4, &res), __builtin_smulll_overflow(4, INT64_MAX / 4, &res));
    printf("%d %d\n", imull_overflow(4, INT64_MIN / 4, &res), __builtin_smulll_overflow(4, INT64_MIN / 4, &res));
    printf("%d %d\n", imull_overflow(4, 3, &res), __builtin_smulll_overflow(4, 3, &res));
    printf("%d %d\n", imull_overflow(1 << 13, 1 << 20, &res), __builtin_smulll_overflow(1 << 13, 1 << 20, &res));
    printf("%d %d\n", imull_overflow(1 << 12, 1 << 20, &res), __builtin_smulll_overflow(1 << 12, 1 << 20, &res));
    printf("%d %d\n", imull_overflow(1ULL << 30, 1ULL << 34, &res),
           __builtin_smulll_overflow(1ULL << 30, 1ULL << 34, &res));
    return 0;
}*/