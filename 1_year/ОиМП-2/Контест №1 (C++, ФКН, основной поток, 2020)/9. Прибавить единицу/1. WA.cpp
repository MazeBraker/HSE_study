#include <iostream>

int main() {
    long long N, K;
    std::cin >> K;
    std::cin >> N;
    std::cout << N % 10 % K << std::endl;
    return 0;
}