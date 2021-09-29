## Разбор задачи «Рациональное число»

### Условие

Напишите класс `Rational` (рациональное число).
Конструктор класса должен получать на вход два числа типа `int` (числитель и знаменатель).
Считайте, что по умолчанию числитель равен 0, а знаменатель — 1.
Переопределите бинарные операторы сложения, вычитания, умножения и деления (работающие в том числе и с аргументами типа `int`), унарные плюс и минус.
Предусмотрите функции-члены `numerator` и `denominator` для получения числителя и знаменателя несократимого представления этой дроби (знаменатель должен быть положительным).
Переопределите также операторы `+=`, `-=`, `*=` и `/=`.
Не забудьте определить операторы `==` и `!=`.
Реализуйте также префиксный и постфиксный операторы `++` и `--`.

### Решение

Будем хранить рацинальное число в виде несократимой дроби. Для этого нам потребуется функция `gcd`, которая появилась в [C++17](https://en.cppreference.com/w/cpp/numeric/gcd).
Впрочем, можно написать самостоятельно её реализацию с помощью [алгоритма Евклида](https://en.wikipedia.org/wiki/Euclidean_algorithm):
```cpp
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
```
Мы введём вспомогательную приватную функцию `reduce`, которая будет сокращать дробь и гарантировать, что знаменатель неотрицателен.
Эту функцию мы будем вызывать всякий раз, когда при вычислениях дробь могла стать сократимой.


```cpp
#include <numeric>

class Rational {
private:
    int num;
    int denom;

    void reduce() {
        int d = std::gcd(num, denom);
        num /= d;
        denom /= d;
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

public:
    Rational(int num_ = 0, int denom_ = 1) : num(num_), denom(denom_) {
        reduce();
    }

    int numerator() const {
        return num;
    }

    int denominator() const {
        return denom;
    }

    // унарный плюс (формально ничего не меняет)
    Rational operator+() const {
        return {num, denom};
    }

    // унарный минус
    Rational operator-() const {
        return {-num, denom};
    }

    // rhs - сокращение от right hand side (правый аргумент бинарного оператора)
    Rational& operator+=(const Rational& rhs) {
        num = num * rhs.denom + rhs.num * denom;
        denom *= rhs.denom;
        reduce();
        return *this;
    }

    Rational& operator-=(const Rational& rhs) {
        num = num * rhs.denom - rhs.num * denom;
        denom *= rhs.denom;
        reduce();
        return *this;
    }

    Rational& operator*=(const Rational& rhs) {
        num *= rhs.num;
        denom *= rhs.denom;
        reduce();
        return *this;
    }

    Rational& operator/=(const Rational& rhs) {
        // сохраняем старый числитель, чтобы корректно работало выражение q /= q.
        int tmp = rhs.num;
        num *= rhs.denom;
        denom *= tmp;
        reduce();
        return *this;
    }

    // префиксный ++
    Rational& operator++() {
        num += denom;
        // здесь нет необходимости вызывать reduce(), так как дробь остаётся несократимой
        return *this;
    }

    Rational& operator--() {
        num -= denom;
        return *this;
    }

    // постфиксный ++ формально определяется с дополнительным игнорируемым параметром типа int
    Rational operator++(int) {
        Rational tmp = *this;
        ++*this;
        return tmp;
    }

    Rational operator--(int) {
        Rational tmp = *this;
        --*this;
        return tmp;
    }
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator() == rhs.numerator() && lhs.denominator() == rhs.denominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}
```