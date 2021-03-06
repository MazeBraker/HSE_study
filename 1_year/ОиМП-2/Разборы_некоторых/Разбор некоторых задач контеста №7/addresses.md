## Разбор задачи «Адреса»

### Условие
Алексею поручили написать программу, обрабатывающую почтовые адреса.

Дана структура `Address` и несколько работающих с ней функций:
```cpp
#pragma once

#include <string>

struct Address {
    std::string Country;
    std::string City;
    std::string Street;
    std::string House;
};

void Parse(const std::string& line, Address * const address);
void Unify(Address * const address);
std::string Format(const Address& address);
```
Функция `Parse` принимает на вход текстовую строчку и пытается выделить из неё компоненты адреса.
Функция `Unify` пытается привести компоненты адреса к каноническому виду (например, вместо «пр-д Кочновский» записать «Кочновский проезд»).
Функция `Format` возвращает текстовое представление адреса.
Функции `Parse` и `Unify`, в духе Google C++ style guide, принимают на вход изменяемые параметры через указатели. Предполагается, что соотвествующие объекты типа `Address` уже созданы.
В случае ошибок обработки адреса функции `Parse` и `Unify` могут сгенерировать исключения.

Алексей написал код обработки, но он почему-то не работает:
```cpp
#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    Address * address;
    while (getline(std::cin, line)) {
        Parse(line, address);
        Unify(address);
        std::cout << Format(*address) << "\n";
    }
}
```
Предполагалось, что эта программа будет читать поступающие на вход строки, извлекать из них адреса и печатать их обработанные текстовые представления.
В случае исключений при обработке строки программа должна напечатать просто "exception" (с переводом строки) и перейти к обработке следующих строк.

Вам нужно исправить ошибки в коде и сдать его в систему.
Код структуры `Address` и функций переписывать не надо: просто подключите в своей программе заголовочный файл `address.h`. Утечек памяти в вашей программе быть не должно.

### Решение
Давайте сначала поймём, в чём фундаментальная ошибка в приведённом неправильном коде обработки.
В нём декларируется указатель `address`, но на какое место в памяти он указывает?
Указатель является примитивным базовым типом.
Локальная переменная `address` никак не инициализируется, и в ней лежит «мусор».
Она **не указывает на адрес реального объекта типа `Address` в памяти**.
Но функции `Parse` и `Unify` предполагают, что переданный указатель ссылается на существующий объект.

Вторая ошибка связана с тем, что в приведённом коде никак не проверяются исключения, которые могут вылететь из функций.

Первый способ решения - создать соответствующую переменную типа `Address` в динамической памяти.
В этом случае мы должны будем вручную следить за её временем жизни и в нужный момент удалить.
Правильнее будет создавать такую переменную всякий раз перед очередным разбором адреса (хотя в условии это не требуется). Однако вот такой код не будет работать:
```cpp
#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    while (getline(std::cin, line)) {
        try {
            Address * address = new Address;
            Parse(line, address);
            Unify(address);
            std::cout << Format(*address) << "\n";
            delete address;
        } catch (...) {
            std::cout << "exception\n";
        }
    }
}
```
Здесь при возникновении исключения мы не дойдём до вызова `delete`, и выделенная память утечёт.
Исправим его так:

```cpp
#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    while (getline(std::cin, line)) {
        Address * address = new Address;
        try {
            Parse(line, address);
            Unify(address);
            std::cout << Format(*address) << "\n";
        } catch (...) {
            std::cout << "exception\n";
        }
        delete address;
    }
}
```

Однако есть решение проще.
Нет никакой необходимости создавать переменную именно в динамической памяти.
Вполне может подойти переменная, созданная просто на стеке.
Тогда в функции `Parse` и `Unify` надо будет передать её адрес,
а в функцию `Format` просто саму эту переменную.
```cpp
#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    while (getline(std::cin, line)) {
        try {
            Address address;
            Parse(line, &address);
            Unify(&address);
            std::cout << Format(address) << "\n";
        } catch (...) {
            std::cout << "exception\n";
        }
    }
}
```
Здесь нам не нужно следить за временем жизни переменной: как бы мы ни покинули блок кода,
локальная стековая переменная будет корректно автоматически уничтожена.