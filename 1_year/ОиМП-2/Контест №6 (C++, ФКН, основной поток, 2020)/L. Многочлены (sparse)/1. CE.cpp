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

    friend Polynomial operator*(const Polynomial &a, const Polynomial &b) {
        Polynomial ans;
        ans.a.resize(a.size() + b.size());
        for (std::size_t i = 0; i != a.size(); ++i)
            for (std::size_t j = 0; j != b.size(); ++j)
                ans.a[i + j] += a[i] * b[j];
        ans.clear();
        return ans;
    }

    friend Polynomial operator+(Polynomial a, const Polynomial &b) {
        return a += b;
    }

    friend Polynomial operator-(Polynomial a, const Polynomial &b) {
        return a -= b;
    }

    Polynomial &operator*=(const Polynomial &p) {
        return *this = *this * p;
    }


    void printsign(std::ostream &str, T x, std::size_t i, bool flag = true) const {
        if (x < T(0)) str << "-", x = -x;
        else if (flag) str << "+";
        if (x != T(1) || i == 0) str << x;
        if (x != T(1) && i != 0) str << "*";
        if (i != 0) {
            str << "x";
            if (i != 1)
                str << "^" << i;
        }
    }

    friend std::ostream &operator<<(std::ostream &str, const Polynomial &p) {
        if (p.size() == 0) return str << T(0);
        for (int i = p.Degree();; --i) {
            if (p[i] != T(0))
                p.printsign(str, p[i], i, i != p.Degree());
            if (i == 0) break;
        }
        return str;
    }
};