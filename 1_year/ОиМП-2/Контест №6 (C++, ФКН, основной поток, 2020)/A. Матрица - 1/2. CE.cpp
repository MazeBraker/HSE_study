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

    Matrix<T> &transpose() {
        auto[col, raw] = size();
        vector<vector<T>> vec;
        for (size_t i = 0; i != raw; ++i) {
            vector<T> vec_raw;
            for (size_t j = 0; j != col; ++j) {
                vec_raw.push_back(v[j][i]);
            }
            vec.push_back(vec_raw);
        }
        v = vec;
        return *this;
    }

    Matrix<T> transposed() const {
        auto[col, raw] = size();
        vector<vector<T>> vec;
        for (size_t i = 0; i != raw; ++i) {
            vector<T> vec_raw;
            for (size_t j = 0; j != col; ++j) {
                vec_raw.push_back(v[j][i]);
            }
            vec.push_back(vec_raw);
        }
        return Matrix<T>(vec);
    }

    class Iterator {
    private:
        vector<vector<T>> &v;
        size_t i;
    public:
        Iterator(vector<vector<T>> &v, size_t i) : v(v), i(i) {}

        bool operator==(const Iterator &that) const {
            return i == that.i;
        }

        bool operator!=(const Iterator &that) const {
            return i != that.i;
        }

        T operator*() {
            return v[i / v[0].size()][i % v[0].size()];
        }

        Iterator &operator++() {
            ++i;
            return *this;
        }
    };

    Iterator begin() {
        return Iterator(v, 0);
    }

    Iterator end() {
        return Iterator(v, v.size() * v[0].size());
    }

    class ConstIterator {
    private:
        const vector<vector<T>> &v;
        size_t i;
    public:
        ConstIterator(const vector<vector<T>> &v, size_t i) : v(v), i(i) {}

        bool operator==(const ConstIterator &that) const {
            return i == that.i;
        }

        bool operator!=(const ConstIterator &that) const {
            return i != that.i;
        }

        T operator*() const {
            return v[i / v[0].size()][i % v[0].size()];
        }

        ConstIterator &operator++() {
            ++i;
            return *this;
        }
    };

    ConstIterator begin() const {
        return ConstIterator(v, 0);
    }

    ConstIterator end() const {
        return ConstIterator(v, v.size() * v[0].size());
    }
};

template<typename T>
ostream &operator<<(ostream &out, const Matrix<T> &m) {
    auto[raw, col] = m.size();
    for (size_t i = 0; i != raw; ++i) {
        for (size_t j = 0; j != col; ++j) {
            out << m[i][j];
            if (j != col - 1)
                out << '\t';
        }
        if (i != raw - 1)
            out << endl;
    }
    return out;
}