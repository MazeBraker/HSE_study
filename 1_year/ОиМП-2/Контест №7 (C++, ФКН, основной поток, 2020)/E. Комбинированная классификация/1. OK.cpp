#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    // Address * address;
    while (getline(std::cin, line)) {
        // Внутри цикла указываем
        Address *address = new Address;
        // try and catch
        try {
            Parse(line, address);
            Unify(address);
            std::cout << Format(*address) << "\n";
        }
        catch (...) {
            std::cout << "exception" << std::endl;
            delete address;
            continue;
        }
        // Чтобы без утечек)
        delete address;
    }
}