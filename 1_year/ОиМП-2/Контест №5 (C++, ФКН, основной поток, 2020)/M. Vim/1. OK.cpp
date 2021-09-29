// Семинар
#include <vector>
#include <utility>

template <typename T>
class Table {
private:
    std::vector<std::vector<T>> tbl;

public:
    Table(size_t n, size_t m) {
        tbl.resize(n);
        for (size_t i = 0; i != n; ++i) {
            tbl[i].resize(m);
        }
    }

    const std::vector<T>& operator[] (size_t i) const {
        return tbl[i];
    }

    std::vector<T>& operator[] (size_t i) {
        return tbl[i];
    }

    void resize(size_t nn, size_t nm) {
        tbl.resize(nn);
        for (size_t i = 0; i != nn; ++i) {
            tbl[i].resize(nm);
        }
    }

    std::pair<size_t, size_t> size() const {
        if (!tbl.empty()) {
            return std::make_pair(tbl.size(), tbl[0].size());
        }
        return std::make_pair(0, 0);
    }
};