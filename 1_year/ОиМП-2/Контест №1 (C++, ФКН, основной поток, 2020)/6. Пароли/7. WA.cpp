#include <iostream>

int main() {
    int x, s = 0;
    std:: cin >> x;
    for (int i = 1; i <= 9; i++) {
        s += x % 10;
        x /= 10;
    }
    std::cout << s;
    return 0;
}
