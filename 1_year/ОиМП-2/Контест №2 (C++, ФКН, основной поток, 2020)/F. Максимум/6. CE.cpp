#include <vector>
#include <iostream>

std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>> &matrix) {
    int ncols = matrix.size();
    int nrows = matrix.begin()->size();
    std::vector<std::vector<int>> trmatrix(ncols);

    for (auto i = 0; i < ncols; i++)
        trmatrix[i].resize(nrows);
    for (auto i = 0; i < ncols; i++) {
        for (auto j = 0; j < nrows; j++)
            trmatrix[i][j] = matrix[j][i];
    }
    return trmatrix;
}