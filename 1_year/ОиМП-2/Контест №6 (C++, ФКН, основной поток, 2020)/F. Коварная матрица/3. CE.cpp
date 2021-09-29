#include <iostream>
#include <vector>

template<class T>
class Polynomial {
public:
    std::vector<T> a;

public:
    Polynomial() {}

    Polynomial(const std::vector<T> &_a) : a(_a) { clear(); }

    Polynomial(const T &x) {
        a.resize(1);
        a[0] = x;
        clear();
    }

    template<class It>
    Polynomial(It begin, It end) {
        while (begin != end) a.push_back(*begin++);
        clear();
    }

    bool operator==(const Polynomial &p) const { return a == p.a; }

    bool operator!=(const Polynomial &p) const { return a != p.a; }

    auto begin() const { return a.begin(); }

    auto end() const { return a.end(); }

    void clear() {
        while (!a.empty() && a.back() == T(0)) a.pop_back();
    }

    std::size_t size() const { return a.size(); }

    int Degree() const {
        return static_cast<int>(a.size()) - 1;
    }

    T operator[](std::size_t ind) const {
        return ind >= size() ? T(0) : a[ind];
    }

    T operator()(const T &x) const {
        T k = 1, ans = 0;
        for (const auto &i : a) {
            ans += k * i;
            k *= x;
        }
        return ans;
    }

    Polynomial &operator+=(const Polynomial &p) {
        for (std::size_t i = 0; i != p.size(); ++i) {
            if (i >= a.size()) a.push_back(0);
            a[i] += p[i];
        }
        clear();
        return *this;
    }

    Polynomial &operator-=(const Polynomial &p) {
        for (std::size_t i = 0; i != p.size(); ++i) {
            if (i >= a.size()) a.push_back(0);
            a[i] -= p[i];
        }
        clear();
        return *this;
    }

    friend Polynomial operator+(Polynomial a, const Polynomial &b) {
        return a += b;
    }

    friend Polynomial operator-(Polynomial a, const Polynomial &b) {
        return a -= b;
    }
};