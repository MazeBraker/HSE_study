// Семинар
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
private:
    vector<vector<T>> v;

public:
    Matrix(const std::vector<std::vector<T>> &inp)
            : v(inp) {
    }

    vector<T> operator[](size_t a) const {
        return v[a];
    }

    vector<T> &operator[](size_t a) {
        return v[a];
    }

    pair<size_t, size_t> size() const {
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