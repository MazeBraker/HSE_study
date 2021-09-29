#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    for (int x = 33; x < 127; x++) {
        printf("%c %3d ", x, x);
        cout << endl;
    }
    return 0;
}