#include "animals.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>
// через умный указатель
using Zoo = std::vector<std::unique_ptr<Animal>>;

Zoo CreateZoo() {
    Zoo zoo;
    std::string word;
    while (std::cin >> word) {
        // нужно чтобы tiger пережил границы этого блока. То есть в динам памяти
        if (word == "Tiger") {
            zoo.push_back(std::unique_ptr<Animal>(new Tiger));
        } else if (word == "Wolf") {
            zoo.push_back(std::unique_ptr<Animal>(new Wolf));
        } else if (word == "Fox") {
            zoo.push_back(std::unique_ptr<Animal>(new Fox));
        } else {
            throw std::runtime_error("Unknown animal!");
        }
    }
    return zoo;
}

// нужно удалить данные из динамической памяти
void Process(const Zoo &zoo) {
    for (const auto &animal : zoo) {
        std::cout << animal->voice() << "\n";
    }
}