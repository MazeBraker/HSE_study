// Семинар
#include <iostream>
#include <tuple>
#include <vector>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> v;

public:
    Matrix(const std::vector<std::vector<T>> &inp)
            : v(inp) {
    }

    std::vector<T> operator[](size_t a) const {
        return v[a];
    }

    std::vector<T> &operator[](size_t a) {
        return v[a];
    }

    std::pair<size_t, size_t> size() const {
        return {v.size(), v.empty() ? 0 : v[0].size()};
    }

    Matrix<T> &operator+=(const Matrix<T> &other) {
        auto[m, n] = other.size();
        for (size_t i = 0; i != m; ++i)
            for (size_t j = 0; j != n; ++j)
                v[i][j] += other[i][j];
        return *this;
    }

    Matrix<T> operator+(const Matrix<T> &other) const {
        Matrix<T> ans(v);
        ans += other;
        return ans;
    }

    template<typename N>
    Matrix<T> &operator*=(const N &number) {
        auto[m, n] = size();
        for (size_t i = 0; i != m; ++i)
            for (size_t j = 0; j != n; ++j)
                v[i][j] = static_cast<T>(v[i][j] * number);
        return *this;
    }

    template<typename N>
    Matrix<T> operator*(const N &number) const {
        Matrix<T> matrix(v);
        matrix *= number;
        return matrix;
    }
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