// 2 задача
// можно ли с помощью short решить? с кастованием в int
#include <stdio.h>

int main() {
    unsigned int  a, b;
    scanf("%u %u", &a, &b);
    if (a % 2 == 0 && b % 2 == 0) {
        a /= 2;
        b /= 2;
    } else if (a % 2 != 0 && b % 2 != 0) {
        a = a / 2 + 1;
        b /= 2;
    } else {
        a /= 2;
        b /= 2;
    }
    printf("%u\n", a + b);
    return 0;
}