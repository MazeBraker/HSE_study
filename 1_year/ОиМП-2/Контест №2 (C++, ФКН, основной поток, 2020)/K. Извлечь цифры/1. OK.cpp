#include <string>
#include <vector>

using namespace std;

void swap_columns(std::vector<std::vector<int>> &matrix, size_t i, size_t j) {
    matrix.push_back(matrix[i]);
    matrix[i] = matrix[j];
    matrix[j] = matrix.back();
    matrix.pop_back();
    return matrix;
}