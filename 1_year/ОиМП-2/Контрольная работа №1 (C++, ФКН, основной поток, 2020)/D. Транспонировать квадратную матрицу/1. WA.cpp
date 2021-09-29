#include <vector>
#include <iostream>

void transpose(std::vector<std::vector<int>>& matrix) {
    int n = matrix[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            matrix[i][j] = matrix[j][i];
    }
}