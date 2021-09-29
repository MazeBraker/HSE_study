#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

bool if_zero(int i) {
    return i == 0;
}

void delete_zeroes(std::vector<int> &numbers) {
    numbers.resize(std::remove_if(numbers.begin(), numbers.end(), if_zero) - numbers.begin());
}