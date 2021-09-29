#include <vector>
#include <iostream>

std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>> &matrix) {
    int x = matrix[0].size();
    int y = matrix.size();
    std::vector<std::vector<int>> trmatrix(x, std::vector<int>(y));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++)
            trmatrix[i][j] = matrix[j][i];
    }
    return trmatrix;
}