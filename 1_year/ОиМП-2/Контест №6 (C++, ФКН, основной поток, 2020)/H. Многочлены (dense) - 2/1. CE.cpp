Matrix operator= (const Matrix& other) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j)
            data[i][j] = other[i][j];
        }
        return *this;
    }
Matrix(const Matrix& other): rows(other.GetRows())
    , columns(other.GetColumns()) {
    data = new T *[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new T[columns];
        for (size_t j = 0; j < columns; ++j)
            data[i][j] = other[i][j];
        }
    }