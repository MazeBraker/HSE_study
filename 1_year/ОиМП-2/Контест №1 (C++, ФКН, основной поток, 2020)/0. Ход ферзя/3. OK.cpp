#include <iostream>

int main() {
    int x;
    int y = 1;
    double s = 0;
    std::cin >> x;
    for (int i = 1; i <= x; ++i) {
        s += 1.0 / (i) * y;
        y *= -1;
    }
    std::cout << s;
    return 0;
}
