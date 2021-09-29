#include <iostream>

int main() {
    int v;
    int t;
    std::cin >> v >> t;
    std::cout << (v * t % 109 + 109) % 109;
    return 0;
}
