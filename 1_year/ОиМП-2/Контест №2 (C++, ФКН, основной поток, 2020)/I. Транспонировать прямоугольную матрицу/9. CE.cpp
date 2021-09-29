#include <string>
#include <vector>

using namespace std;

void swap_columns(std::vector<std::vector<int>> &matrix, size_t i, size_t j) {
    int temp;
    for (int i = 0; i < matrix.size(); i++) {
        temp = matrix[i][i];
        matrix[i][i] = matrix[i][j];
        matrix[i][j] = temp;
    }
}