### Разбор задачи Многочлены (dense)

При реализации этого класса, я полагаюсь на то, что вы уже прочли и знаете условие. Если это не так, то с ним можно ознакомиться по [ссылке](https://gist.github.com/cdraugr/7bea4b26cc4e171736a6e41be30f611c). Я буду реализовывать класс по пунктам условия, чтобы вам было проще следить за происходящим.

```c++
#include <algorithm>
#include <cstdint>  // for fixed width integer type
#include <iostream>
#include <vector>

template <typename T>
class Polynomial {
public:
    using i64 = std::int64_t;
    using Container = typename std::vector<T>;
    using ConstIterator = typename Container::const_iterator;

private:
    Container coefficients_;
    inline static const T value_type_zero{0};

    void _normalize() {
        while (!coefficients_.empty() && coefficients_.back() == value_type_zero) {
            coefficients_.pop_back();
        }
    }

    Container& GetCoeffs() {
        return coefficients_;
    }

public:
    Polynomial(const Container& coefficients)
        : coefficients_{coefficients} {
            _normalize();
        }

    Polynomial(const T& value = {}) {
        if (value != value_type_zero) {
            coefficients_.push_back(value);
        }
    }

    template<typename ForwardIt>
    Polynomial(ForwardIt first, ForwardIt last)
        : coefficients_{first, last} {
            _normalize();
    }

    const Container& GetCoeffs() const {
        return coefficients_;
    }
```

Прочитав задание полностью, давайте договоримся сохрананять инвариант: последний элемент всегда ненулевой. Это будет полезно при реализации. Для поддержания этого инварианта я реализовал функцию `_normalize()`, которая удаляет все последние нули в нашем векторе. Там же, в приватном поле, я храню константное значение типа `T`, равное нулю. Это позволяет создавать объект этого типа для проверки на равенство с нулём только один раз. Я сделал его `static`, а ключеве слово `inline` позволяет мне инициализировать эту переменную в той же строке, где я её объявляю.

Хранить же наши коэффициенты будем в векторе, где `coefficients_[i]` будет значить, что мы смотрим на коэффициент перед `x^i`. У вектора есть конструктор копирования, чем мы и пользуемся при реализации конструктора, который принимает вектор. Аналогично с конструктором, который принимает два итератора. Конструктор, создающий многочлен по заданному коэффициенту будет добавлять в наш вектор этот самый коэффициент, только если он не ноль. Это позволяет лишний раз не вызывать `_normalize()`.

Для удобства реализации я написал константную и неконстантную версии функции `GetCoeffs()`, которая возвращает наш вектор. Так как я не хочу, чтобы пользователь мог что-то менять внутри - нарушать инвариант, например, я объявил неконстантную версию в `private`, а константную в `public`.

---

```c++
    friend bool operator==(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs.GetCoeffs() == rhs.GetCoeffs();
    }

    friend bool operator!=(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return !(lhs == rhs);
    }
```

У `std::vector` переопределён `operator==`, чем я и пользуюсь тут.

Так как при декларации конструктора класса не используется ключевое слово `explicit`, операторы будут работать и в том случае, когда один из аргументов является скаляром.

---

```c++
    Polynomial<T>& operator+=(const Polynomial<T>& other) {
        if (other.Degree() > Degree()) {
            GetCoeffs().resize(other.Degree() + 1);
        }

        for (i64 i = 0; i <= Degree() && i <= other.Degree(); ++i) {
            GetCoeffs()[i] += other.GetCoeffs()[i];
        }
        _normalize();
        return *this;
    }

    Polynomial<T>& operator-=(const Polynomial<T>& other) {
        if (other.Degree() > Degree()) {
            GetCoeffs().resize(other.Degree() + 1);
        }

        for (i64 i = 0; i <= Degree() && i <= other.Degree(); ++i) {
            GetCoeffs()[i] -= other.GetCoeffs()[i];
        }
        _normalize();
        return *this;
    }

    Polynomial<T>& operator*=(const Polynomial<T>& other) {
        if (Degree() == -1 || other.Degree() == -1) {
            GetCoeffs().resize(0);
            return *this;
        }

        std::vector<T> tmp(Degree() + other.Degree() + 1);
        for (i64 i = 0; i <= Degree(); ++i) {
            for (i64 j = 0; j <= other.Degree(); ++j) {
                tmp[i + j] += GetCoeffs()[i] * other.GetCoeffs()[j];
            }
        }
        GetCoeffs() = std::move(tmp);
        _normalize();
        return *this;
    }
```

В реализации этих методов я использую ещё нереализованную функцию `Degree()`. Я реализую её чуть позже (когда до неё дойдёт очередь). Всё что нам надо знать сейчас - она возвращает степень полинома, а если полином равен нулю, то `-1`.

Все три оператора изначально делают `resize()`, чтобы не случился проезд по памяти если оно того стоит (а в умножении точно стоит) и согласно правилам математики складывают, вычитают или умножают два многочлена. При этом в умножении рассматривается отдельно краевой случай, когда один из полиномов равен нулю.

```c++
    friend Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs += rhs;
    }

    friend Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs -= rhs;
    }

    friend Polynomial<T> operator*(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs *= rhs;
    }
```

`lhs` будем принимать не по ссылке, а создавать копию на лету, это позволит нам её сразу же изменить применив соответствующий оператор и вернуть её же.

---

```c++
    i64 Degree() const {
        return static_cast<i64>(GetCoeffs().size()) - 1;
    }

    const T& operator[](size_t power) const {
       return static_cast<i64>(power) > Degree() ? value_type_zero : GetCoeffs()[power];
    }
```

Посмотрите на сколько тут нам помог инвариант, что последний элемент всегда ненулевой. Мы не храним ненужные нули, из-за чего `Degree()` пишется в одну строку.

Очень важным хочу отметить, что если бы мы не задавали `value_type_zero` и писали бы тут `static_cast<T>(0)`, то при реализации `operator[]` пришлось бы возвращать копию, а не константную ссылку. При этой же реализации, мы избавляемся от ненужных копирований.

---

```c++
    T operator()(const T& given_value) const {
        T result = value_type_zero;

        for (auto i = Degree(); i >= 0; --i) {
            result *= given_value;
            result += GetCoeffs()[i];
        }

        return result;
    }
```

Так как нас просят написать эффективный код, давайте немного подумаем и вспомним школьную программу. Из школы нам известен алгоритм Горнера. Им мы и воспользуемся.

При этом, если у наш многочлен равен нулю, то мы не зайдём в цикл и вернём ноль. Отдельно этот случай рассматривать не надо.

---

```c++
    ConstIterator begin() const {
        return GetCoeffs().cbegin();
    }

    ConstIterator end() const {
        return GetCoeffs().cend();
    }
```

Реализацию `operator<<` я оставил напоследок. Так что пока рассмотрим методы `begin()` и `end()`. Как нам и сказано в условии: `это могут быть просто итераторы вектора`, мы просто возвращаем константные итераторы нашего вектора. При этом можно было бы написать `return GetCoeffs().begin()` и `.end()`, но `c` в названии подчёркивает константность.

---

```c++
    friend Polynomial<T> operator&(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        Polynomial<T> result;  // = 0 as default;

        for (auto i = lhs.Degree(); i >= 0; --i) {
            result *= rhs;
            result += lhs[i];
        }

        return result;
    }
```

Реализация `operator&` очень похожа на реализацию `operator()`. Оно и понятно, мы делаем ровно те же операции с ровно теми же идеями. Реализация этого оператора без дублирования кода будет ниже.

---

```c++
    friend Polynomial<T> operator/(Polynomial<T> lhs, const Polynomial<T>& rhs) {
        if (lhs.Degree() < rhs.Degree() || lhs.Degree() == -1) {
            return {};
        }

        const auto quotient = lhs[lhs.Degree()] / rhs[rhs.Degree()];
        if (lhs.Degree() == rhs.Degree()) {
            return {quotient};
        }

        Container answer(lhs.Degree() - rhs.Degree() + 1);
        answer.back() = quotient;

        for (auto i = lhs.Degree(); i >= lhs.Degree() - rhs.Degree(); --i) {
            lhs.GetCoeffs()[i] = lhs[i] - rhs[rhs.Degree() - lhs.Degree() + i] * quotient;
        }
        lhs._normalize();
        return answer + lhs / rhs;
    }
```

Деление заслуживает отдельного рассмотрения. Перед вами простая реализация деления в столбик. Если делимое ноль или его степень меньше степени делителя, то мы возвращаем ноль. Так же хочу отметить, что при вызове `polynomial / 0` произойдёт неопределённое поведение.

Если степени полиномов равны, то мы вернём частное от деления коэффициентов, стоящих перед `x` в старшей степени. Во всех иных случаях делаем один шаг деления в столбик и повторям весь процесс пока делится.

---

```c++
    friend Polynomial<T> operator%(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs - (lhs / rhs) * rhs;
    }

    friend Polynomial<T> operator,(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        if (lhs == lhs.value_type_zero) {
            if (rhs.Degree() != -1) {
                return rhs / rhs[rhs.Degree()];
            }
            return rhs;
        }
        return (rhs % lhs, lhs);
    }
};
```

Остаток от деления и НОД реализуются просто.

При подсчёте остатка, мы пользуемся тем, что деление округляет до "целого" вниз, т.е. отбрасывает дробную часть.

Для подсчёта наибольшего общего делителя будем использовать алгоритм Евклида. При этом не забудем, что `gcd(0, 0)` равен нулю, и в таком случае `Degree()` внернёт `-1`. Проезда по памяти мы не хотим, так что рассмотрим этот случай отдельно.

---

```c++
template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynomial) {
    const T zero = static_cast<T>(0), one = static_cast<T>(1),
            minus_one = static_cast<T>(-1);
    if (polynomial.Degree() == -1) {
        return out << zero;
    }

    bool first_written = false;
    for (auto degree = polynomial.Degree(); degree >= 0; --degree) {
        const auto& coefficient = polynomial[degree];
        if (coefficient == zero) {
            continue;
        }

        if (coefficient > zero && first_written) {
            out << '+';
        } else if (degree > 0 && coefficient == minus_one) {
            out << '-';
        }

        if (!degree || (coefficient != one && coefficient != minus_one)) {
            out << coefficient;
            if (degree > 0) {
                out << '*';
            }
        }

        if (degree > 0) {
            out << 'x';
            if (degree > 1) {
                out << '^' << degree;
            }
        }
        first_written = true;
    }
    return out;
}
```

Оператор `<<` я оставил напоследок, потому что его принято реализовывать вне класса. Не забываем рассмотреть случай с пустым многочленом и вывести ноль. Далее мы проходимся по всем коэффициентам с конца и пропускаем нулевые. Когда же мы встретили ненулевой, печатаем `+`, если число положительное и это не первый символ для печати, или `-`, если мы встретили `-1` и мы рассматривает коэффициент не перед `x^0`. Далее просто выводим коэффициент и `x^i`, если это требуется.

---

Как и обещалось, реализация бинарного оператора `&` без дублирования кода:

```c++
    friend Polynomial<T> operator&(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        Polynomial<Polynomial<T>> result(lhs.begin(), lhs.end());
        return result(rhs);
    }
```

Достаточно прочесть условие и всё станет ясно:

> Перегрузите бинарный оператор `&` для вычисления композиции многочленов: `(f & g)(x)` должно равняться `f(g(x))`.

Задаём полином от полиномов (т.е. тут "коэффициентами" будут являться полиномы), а дальше вызываем уже реализованный `operator()`, в который передаём полином. Просто и красиво.

---
