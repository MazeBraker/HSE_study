// Cеминар
#include <iostream>
#include <cassert>
#include <vector>

template <typename T>
class Matrix {
    size_t M, N;
    std::vector<std::vector<T>> matrix;

public:
    class MatrixIter {
        std::vector<std::vector<T>> &matr;
        size_t cur;
    public:
        MatrixIter(std::vector<std::vector<T>> &_a, size_t _cur): matr(_a), cur(_cur) {}

        bool operator==(const MatrixIter &b) const {
            return cur == b.cur;
        }

        bool operator!=(const MatrixIter &b) const {
            return cur != b.cur;
        }

        MatrixIter& operator++ () {
            ++cur;
            return *this;
        }


        T & operator*() {
            size_t a = cur % matr[0].size(), b = cur / matr[0].size();
            return matr[b][a];
        }
    };

    MatrixIter begin() {
        return MatrixIter(matrix, 0);
    }

    MatrixIter end() {
        return MatrixIter(matrix, M * N);
    }

    class MatrixIter_c {
        const std::vector<std::vector<T>> &matr;
        size_t cur;
    public:
        MatrixIter_c(const std::vector<std::vector<T>> &_a, size_t _cur): matr(_a), cur(_cur) {}

        bool operator==(const MatrixIter_c &b) const {
            return cur == b.cur;
        }

        bool operator!=(const MatrixIter_c &b) const {
            return cur != b.cur;
        }

        MatrixIter_c & operator++ () {
            ++cur;
            return *this;
        }


        T operator*() const {
            size_t a = cur % matr[0].size(), b = cur / matr[0].size();
            return matr[b][a];
        }
    };


    MatrixIter_c begin() const {
        return MatrixIter_c(matrix, 0);
    }

    MatrixIter_c end() const {
        return MatrixIter_c(matrix, M * N);
    }


    Matrix(const std::vector<std::vector<T>>& a) : matrix(a) {
        M = a.size();
        N = a[0].size();
    }

    std::pair<size_t, size_t> size() const {
        return std::make_pair(M, N);
    }

    Matrix<T>& transpose() {
        std::vector<std::vector<T>> a(N, std::vector<T>(M));
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                a[i][j] = matrix[j][i];
        matrix = a;
        M = matrix.size();
        N = matrix[0].size();
        return *this;
    }

    Matrix<T> transposed() const {
        Matrix<T> a(matrix);
        a.transpose();
        return a;
    }

    template <typename U>
    friend std::ostream& operator<< (std::ostream& out, const Matrix<U>& m);

    template <typename U>
    friend Matrix<U> operator+ (const Matrix<U>& a, const Matrix<U>& b);

    template <typename U>
    friend Matrix<U>& operator+= (Matrix<U>& a, const Matrix<U>& b);

    template <typename U>
    friend Matrix<U> operator* (const Matrix<U>& a, const int& b);

    template <typename U>
    friend Matrix<U> operator* (const Matrix<U>& a, const Matrix<U>& b);

    template <typename U>
    friend Matrix<U>& operator*= (Matrix<U>& a, const int& b);

    template <typename U>
    friend Matrix<U>& operator*= (Matrix<U>& a, const Matrix<U>& b);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
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

template <typename T>
Matrix<T> operator+ (const Matrix<T>& a, const Matrix<T>& b) {
    Matrix<T> c(a);
    for (size_t i = 0; i < a.size().first; ++i)
        for (size_t j = 0; j < a.size().second; ++j)
            c.matrix[i][j] += b.matrix[i][j];
    return c;
}

template <typename T>
Matrix<T>& operator+= (Matrix<T>& a, const Matrix<T>& b) {
    a = a + b;
    return a;
}

template <typename T>
Matrix<T> operator* (const Matrix<T>& a, const int& b) {
    Matrix<T> c(a);
    for (size_t i = 0; i < a.size().first; ++i)
        for (size_t j = 0; j < a.size().second; ++j)
            c.matrix[i][j] *= b;
    return c;
}
template <typename T>
Matrix<T> operator* (const Matrix<T>& a, const Matrix<T>& b) {
    assert(a.size().second == b.size().first);
    Matrix<T> c(std::vector<std::vector<T>>(a.size().first, std::vector<T>(b.size().second)));
    for (size_t i = 0; i < a.size().first; i++)
        for (size_t j = 0; j < b.size().second; j++)
            for (size_t k = 0; k < a.size().second; k++)
                c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
    return c;
}

template <typename T>
Matrix<T>& operator*= (Matrix<T>& a, const int& b) {
    a = a * b;
    return a;
}

template <typename T>
Matrix<T>& operator*= (Matrix<T>& a, const Matrix<T>& b) {
    a = a * b;
    return a;
}