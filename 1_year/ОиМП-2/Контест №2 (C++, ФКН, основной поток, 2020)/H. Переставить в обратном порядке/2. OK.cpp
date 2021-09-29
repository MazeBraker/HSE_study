std::pair<size_t, size_t> max_element(const std::vector<std::vector<int>>& matrix) {
    std::pair<size_t, size_t> max_element = {0, 0};
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] > matrix[max_element.first][max_element.second]) {
                max_element.first = i;
                max_element.second = j;
            }
        }
    }
    return max_element;
}