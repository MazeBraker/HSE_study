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
        if (v.empty()) {
            return {v.size(), (0)};
        } else {
            return {v.size(), (v[0].size())};
        }
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
    auto[raw, col] = m.size();
    for (size_t i = 0; i != raw; ++i) {
        for (size_t j = 0; j != col; ++j) {
            out << m[i][j];
            if (j != col - 1)
                out << '\t';
        }
        if (i != raw - 1)
            out << '\n';
    }
    return out;
}