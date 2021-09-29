// 4 прога
#include <stdio.h>

int main() {
    long long a, b, n, k = 1, w = 2, i, j;
    scanf("%lld %lld %lld", &a, &b, &n);
    // сначала хочу напечатать интервал а,б с отступом, потом саму таблицу сразу
    for (i = a; i < b; ++i) {
        printf("%*lld", (int) (w * n + 1), i);
        w = 1;
    }
    printf("\n");
    for ( i = a; i < b; ++i) {
        // Как сделать выравнивание?
        k = i;
        // костыль для первой табуляции
        printf("%*lld", (int)n, k);
        for ( j = a; j < b; ++j) {
            printf("%*lld", (int)(n + 1), i * j);
        }
        // костыль для последней табуляции
        if (i == b - 1) {
        	printf("\n");
            return 0;
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}