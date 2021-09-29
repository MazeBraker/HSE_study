#include <stdio.h>

int main() {
    unsigned long long start, finish, sum = 0;
    //https://stackoverflow.com/questions/30065675/what-does-scanf-nc-mean/30070821
    while (scanf("%llx-%llx %*[^\n]", &start, &finish) == 2) {
        sum += finish - start;
    }
    printf("%llu\n", sum);
    return 0;
}