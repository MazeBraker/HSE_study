#include <string>
#include <vector>

using namespace std;

void swap_columns(std::vector<std::vector<int>> &matrix, size_t i, size_t j) {
    int temp;
    for (int i = 0; i < matrix.size(); i++) {
        temp = matrix[i][size_t i];
        matrix[i][size_t i] = matrix[i][size_t j];
        matrix[i][size_t j] = temp;
    }
}