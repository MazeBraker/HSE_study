#include <vector>
#include <string>
using namespace std;

void swap_columns(std::vector<std::vector<int>> &matrix, size_t i, size_t j) {
    int temp;
    for (int x = 0; e < matrix.size(); x++) {
        temp = matrix[e][i];
        matrix[x][i] = matrix[x][j];
        matrix[x][j] = temp;
    }
}