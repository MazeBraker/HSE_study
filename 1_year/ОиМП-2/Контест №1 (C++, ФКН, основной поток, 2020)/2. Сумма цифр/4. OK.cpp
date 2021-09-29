#include <iostream>

int main() {
    int x, s = 0;
    std::cin >> x;
    while (x != 0) {
        s += x % 10;
        x /= 10;
    }
    std::cout << s;
    return 0;
}