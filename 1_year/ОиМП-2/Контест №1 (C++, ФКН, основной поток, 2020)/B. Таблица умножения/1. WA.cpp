#include <iostream>

int main() {
    int x;
    std:: cin >> x;
    if (x % 7 == 1)
        std::cout <<"mon";
    if (x % 7 == 2)
        std::cout <<"tue";
    if (x % 7 == 3)
        std::cout <<"wed";
    if (x % 7 == 4)
        std::cout <<"thu";
    if (x % 7 == 5)
        std::cout <<"fri";
    if (x % 7 == 6)
        std::cout <<"sat";
    if (x % 7 == 0)
        std::cout <<"sun";
    return 0;
}
