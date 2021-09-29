#include <vector>
#include <string>
void reverse(std::vector<int>& numbers) {
    int a = numbers.size() - 1;
    std::vector<int> newvec;
    for (int i = a; i >= 0; i--) {
        newvec.push_back(numbers[i]);
    }
    numbers = newvec;
}