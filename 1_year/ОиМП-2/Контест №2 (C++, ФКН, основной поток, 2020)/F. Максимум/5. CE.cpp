std::pair<size_t, size_t> max_element(const std::vector<std::vector<int>> &matrix) {
    std::pair<size_t, size_t> maxElemIndex(0, 0);
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] > matrix[maxElemIndex.first][maxElemIndex.second]) {
                maxElemIndex.first = i;
                maxElemIndex.second = j;
            }
        }
    }
    return maxElemIndex;
}