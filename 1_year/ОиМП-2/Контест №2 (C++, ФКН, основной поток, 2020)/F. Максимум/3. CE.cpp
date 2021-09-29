#include <vector>
#include <string>

using namespace std;

void swap_columns(std::vector<std::vector<int>> &matrix, size_t i, size_t j) {
    int temp;
    for (int x = 0; x < matrix.size(); x++) {
        temp = matrix[x][i];
        matrix[x][i] = matrix[x][j];
        matrix[x][j] = temp;
    }
}