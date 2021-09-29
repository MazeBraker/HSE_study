// Семинар
#include <iostream>
#include <vector>

template <typename T>
class Polynomial {
private:
    std::vector <T> cfs;

public:
    Polynomial(const std::vector<T> &v) : cfs(v) {}

    template <typename Iter>
    Polynomial(Iter first, Iter last) {
        std::copy(first, last, std::back_inserter(cfs));
    }

    Polynomial(T a = 0) {
        cfs = {a};
    }

    friend bool operator==(const Polynomial<T> &th, const Polynomial<T> &oth) {
        return th.cfs == oth.cfs;
    }

    friend bool operator!=(const Polynomial<T> &th, const Polynomial<T> &oth) {
        return th.cfs != oth.cfs;
    }

    Polynomial<T>& operator+= (const Polynomial<T> &oth) {
        cfs.resize(std::max(cfs.size(), oth.cfs.size()));
        for (size_t i = 0; i < cfs.size(); ++i) {
            if (i < oth.cfs.size())
                cfs[i] += oth.cfs[i];
        }
        Popper();
        return *this;
    }

    friend Polynomial<T> operator+ (const Polynomial<T> &th, const Polynomial<T> &oth) {
        Polynomial<T> tmp = th;
        tmp += oth;
        return tmp;
    }

    Polynomial<T>& operator-= (const Polynomial<T> &oth) {
        cfs.resize(std::max(cfs.size(), oth.cfs.size()));
        for (size_t i = 0; i < cfs.size(); ++i) {
            if (i < oth.cfs.size())
                cfs[i] -= oth.cfs[i];
        }
        Popper();
        return *this;
    }

    friend Polynomial<T> operator- (const Polynomial<T> &th, const Polynomial<T> &oth) {
        Polynomial<T> tmp = th;
        tmp -= oth;
        return tmp;
    }

    Polynomial<T>& operator*= (const Polynomial<T> &oth) {
        std::vector<T> tmp = cfs;
        std::vector<T> tmp1 = oth.cfs;
        size_t s1 = cfs.size() - 1;
        size_t s2 = oth.cfs.size() - 1;
        cfs.clear();
        cfs.resize(s1 * s2 + 1);
        for (size_t i = 0; i < tmp.size(); ++i) {
            for (size_t j = 0; j < tmp1.size(); ++j) {
                cfs[i + j] += tmp[i] * tmp1[j];
            }
        }
        Popper();
        return *this;
    }

    friend Polynomial<T> operator* (const Polynomial<T> &th, const Polynomial<T> &oth) {
        Polynomial<T> tmp = th;
        tmp *= oth;
        return tmp;
    }

    auto begin() const {
        return cfs.begin();
    }

    auto end() const {
        return cfs.end();
    }

    T operator[](size_t i) const {
        if (i >= cfs.size())
            return 0;
        return cfs[i];
    }

    int Degree() const {
        if (cfs == {0})
            return -1;
        return cfs.size() - 1;
    }

    void Popper() {
        while (cfs.back() == 0) {
            cfs.pop_back();
        }
        if (cfs.empty())
            cfs = {0};
    }
};
