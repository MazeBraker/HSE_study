## Разбор задачи «Optional»

### Условие
Напишите свою реализацию класса [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional),
который может либо хранить элемент, либо хранить метку об отсутствии элемента.

Вот заготовка для вашего класса:
```cpp
// Это исключение нужно генерировать в функции value
// при обращении к пустому объекту Optional
struct BadOptionalAccess {
};

template <typename T>
class Optional {
private:
    // alignas нужен для правильного выравнивания блока памяти
    alignas(T) unsigned char data[sizeof(T)];
    bool defined = false;

public:
    Optional() = default;
    Optional(const T& elem);
    Optional(T&& elem);
    Optional(const Optional& other);

    Optional& operator=(const Optional& other);
    Optional& operator=(const T& elem);
    Optional& operator=(T&& elem);

    bool has_value() const;

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    T& value();
    const T& value() const;

    void reset();

    ~Optional();
};
```
Вам нужно вписать сюда реализацию функций класса и сдать класс с функциями в систему.

Обратите внимание, что `Optional`, в отличие от `unique_ptr`, должен хранить данные на стеке, а не в динамической памяти.
Эти данные нужно проинициализировать только при необходимости (по умолчанию `Optional` создаётся пустым).
Для этого нужно использовать конструкцию [placement new](https://ru.wikipedia.org/wiki/New_(C%2B%2B)#Placement_new) – явное указание компилятору создать объект в указанном месте памяти.
Например, сконструировать новый объект типа `T` в блоке памяти data можно так: `new (data) T()`.
За временем жизни такого объекта придётся следить самостоятельно.
Сама сырая память `data` в данном случае будет удалена автоматически, но деструктор придётся позвать вручную: `reinterpret_cast<T*>(data)->T()`.
Запомните: конструирование объекта с помощью placement new в уже имеющейся памяти, как в этой задаче, – это единственный случай, когда которого нужно вызывать деструктор самостоятельно.

Старайтесь не создавать лишние объекты типа `T` зря.
Например, при присваивании нового объекта уже заполненному `Optional` просто вызовите соответствующий оператор присваивания для типа `T`.

Вот [код нашей тестовой программы](https://clck.ru/FLoZo), который вам поможет в отладке.
Вы можете сравнить её вывод для вашего класса и для стандартного `std::optional`.

Заметим, что настоящий `std::optional` реализован сложнее.
Просто конструировать объект в буфере байт на стеке он не может: тогда такой `std::optional` нельзя было бы использовать в `constexpr`-выражениях.
Вместо этого в стандартном `std::optional` применяется `union`.
Однако в этой задаче вполне достаточно использовать обычный буфер.

Не пытайтесь использовать в своём решении стандартный `std::optional`: это не скомпилируется.

### Решение
Конструирование элемента в конструкторе `Optional` будет выглядеть так:
```cpp
Optional(const T& elem) {
    new (data) T(elem);  // размещающий оператор new
    defined = true;
}
```
Если на вход конструктора подаётся временный объект, то надо передать его в конструктор типа `T` тоже как временный, несмотря на то, что он приобрёл у нас имя `elem`:
```cpp
Optional(T&& elem) {
    new (data) T(std::move(elem));
    defined = true;
}
```
В конструкторах надо использовать вызов конструктора типа `T`, а в операторах присваивания, если объект типа `T`, уже был создан, – вызов оператора присваивания, чтобы сохранить семантику.
При этом надо помнить, что в конструкторе мы создаём новый `Optional` (и его старого состояния не существует), а в операторе присваивания – меняем уже существующий:
```cpp
Optional& operator=(const T& elem) {
    if (defined) {
        **this = elem;  // вызов перегруженного operator* для текущего объекта
    } else {
        new (data) T(elem);
        defined = true;
    }
    return *this;
}

```
Напишем функцию `reset` (она пригодится в деструкторе и в присваивании):
```cpp
void reset() {
    if (defined) {
        value().~T();  // явный вызов деструктора является парным к placement new
        defined = false;
    }
}

```
В терминах `reset` напишем присваивание одного `Optional` другому:
```cpp
Optional& operator=(const Optional& other) {
    if (!other.defined) {
        reset();
    } else if (defined) {
        **this = *other;  // присваиваем, если старый объект существовал
    } else {
        new (data) T(*other);  // конструируем, если старого объекта не существовало
        defined = true;
    }
    return *this;
}

```


Соберём теперь всё вместе и допишем недостающие функции:

```cpp
#include <utility>

struct BadOptionalAccess {
};

template <typename T>
class Optional {
private:
    alignas(T) unsigned char data[sizeof(T)];
    bool defined = false;

public:
    Optional() = default;
    Optional(const T& elem) {
        new (data) T(elem);
        defined = true;
    }
    Optional(T&& elem) {
        new (data) T(std::move(elem));
        defined = true;
    }
    Optional(const Optional& other) {
        if (other.defined) {
            new (data) T(*other);
            defined = true;
        }
    }
    Optional& operator=(const Optional& other) {
        if (!other.defined) {
            reset();
        } else if (defined) {
            **this = *other;
        } else {
            new (data) T(*other);
            defined = true;
        }
        return *this;
    }
    Optional& operator=(const T& elem) {
        if (defined) {
            **this = elem;
        } else {
            new (data) T(elem);
            defined = true;
        }
        return *this;
    }
    Optional& operator=(T&& elem) {
        if (defined) {
            **this = std::move(elem);
        } else {
            new (data) T(std::move(elem));
            defined = true;
        }
        return *this;
    }
    bool has_value() const {
        return defined;
    }
    T& operator*() {
        return *reinterpret_cast<T*>(data);
    }
    const T& operator*() const {
        return *reinterpret_cast<const T*>(data);
    }
    T* operator->() {
        return reinterpret_cast<T*>(data);
    }
    const T* operator->() const {
        return reinterpret_cast<const T*>(data);
    }
    T& value() {
        if (!defined) {
            throw BadOptionalAccess();
        }
        return **this;
    }
    const T& value() const {
        if (!defined) {
            throw BadOptionalAccess();
        }
        return **this;
    }
    void reset() {
        if (defined) {
            value().~T();
            defined = false;
        }
    }
    ~Optional() {
        reset();
    }
};
```