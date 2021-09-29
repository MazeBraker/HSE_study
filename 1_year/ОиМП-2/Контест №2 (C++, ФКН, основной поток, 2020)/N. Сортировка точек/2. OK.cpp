#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (int i : str) {
        if (i == delimiter) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += i;
        }
    }
    tokens.push_back(token);
    return tokens;
}