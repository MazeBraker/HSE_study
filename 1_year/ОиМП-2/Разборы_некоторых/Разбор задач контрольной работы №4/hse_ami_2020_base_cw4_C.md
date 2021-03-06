## Разбор задачи «Снова жизнь объекта»

### Условие
Вам дан класс `A` и функция `main()`:
```cpp
#include <iostream>
#include <memory>

class A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const {
        std::cout << "A::foo()\n";
    }
};

#include "your_code.h"

int main() {
    std::unique_ptr<A> ptr(new B);
    ptr->foo();
}
```

Напишите такой код класса `B`, чтобы функция `main()` вывела бы сообщения:
```
Constructor(int): 42
Constructor(int): 17
A::foo()
Destructor
Destructor
```

Не пытайтесь вывести нужный текст с помощью непосредственной печати: мы при проверке всё равно заменяем отладочные сообщения в классе на свои.


### Решение
Из строчки `std::unique_ptr<A> ptr(new B)`
становится понятно, что тип `B*` должен приводиться к типу `A*`.
Это возможно, если, например, `B` является наследником класса `A`.

Ещё мы видим, что при инициализации объекта типа `B`
должны сконструироваться два объекта типа `A` с аргументами 42 и 17.
Про один из них мы знаем: это должен быть подобъект базового класса,
который неявно вкладывается в `B` при наследовании.
А вот второй объект можно принести, например, в виде композиции.
В конструкторе класса `B` важно проинициализировать объекты нужными аргументами:
сначала подобъект базового класса, затем — поле.
```cpp
class B: public A {
    A field;
public:
    B(): A(42), field(17) {
    }
};
```