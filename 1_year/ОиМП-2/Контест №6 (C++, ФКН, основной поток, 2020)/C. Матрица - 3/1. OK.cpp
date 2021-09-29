#include <iostream>
#include <tuple>
#include <vector>


template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> v;

public:
    [[nodiscard]] std::pair<size_t, size_t> size() const {
        return {v.size(), v.empty() ? 0 : v[0].size()};
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