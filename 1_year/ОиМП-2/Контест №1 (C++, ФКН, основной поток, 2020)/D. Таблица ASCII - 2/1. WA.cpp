#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    for (int x = 32; x < 128; x++) {
        if (x % 16 == 0) printf("\n");
        printf("%c    ", x);
    }
    return 0;
}