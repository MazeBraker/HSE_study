// Cеминар
#include <iostream>
#include <cassert>
#include <vector>

template<typename T>
class Matrix {
    size_t M, N;
    std::vector<std::vector<T>> matrix;
public:
    Matrix(const std::vector<std::vector<T>> &a) : matrix(a) {
        M = a.size();
        N = a[0].size();
    }

    std::pair<size_t, size_t> size() const {
        return std::make_pair(M, N);
    }

    template<typename U>
    friend std::ostream &operator<<(std::ostream &out, const Matrix<U> &m);

    template<typename U>
    friend Matrix<U> operator+(const Matrix<U> &a, const Matrix<U> &b);

    template<typename U>
    friend Matrix<U> &operator+=(Matrix<U> &a, const Matrix<U> &b);
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
    for (size_t i = 0; i < m.size().first; ++i) {
        for (size_t j = 0; j < m.size().second; ++j) {
            out << m.matrix[i][j];
            if (j < m.size().second - 1)
                out << '\t';
        }
        if (i < m.size().first - 1)
            out << '\n';
    }
    return out;
}

template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) {
    Matrix<T> c(a);
    for (size_t i = 0; i < a.size().first; ++i)
        for (size_t j = 0; j < a.size().second; ++j)
            c.matrix[i][j] += b.matrix[i][j];
    return c;
}

template<typename T>
Matrix<T> &operator+=(Matrix<T> &a, const Matrix<T> &b) {
    a = a + b;
    return a;
}