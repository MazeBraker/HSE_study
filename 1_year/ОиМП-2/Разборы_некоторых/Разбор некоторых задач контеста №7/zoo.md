## Разбор задачи «Зоопарк»

### Условие
Вы работаете с иерархией классов, описывающих животных:
```cpp
#pragma once

#include <string>

class Animal {
public:
    virtual std::string voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal() {
    }
};

class Tiger: public Animal {
    std::string voice() const override {
        return "Rrrr";
    }
};

class Wolf: public Animal {
    std::string voice() const override {
        return "Wooo";
    }
};

class Fox: public Animal {
    std::string voice() const override {
        return "Tyaf";
    }
};
```
Вам нужно определить тип `Zoo`, представляющий из себя набор различных животных, и написать две функции: `Zoo CreateZoo()` и `void Process(const Zoo& zoo)`.

Функция `CreateZoo` должна читать слова из стандартного ввода.
Если на вход поступают слова `Tiger`, `Wolf` или `Fox`, она должна поместить соответствующего зверя в зоопарк.
Если на вход поступает другое слово, она должна прекратить чтение и сгенерировать исключение `std::runtime_error`.

Функция `Process` должна перебрать всех зверей в зоопарке в порядке создания и напечатать для каждого из них результат работы виртуальной функции `voice`.

Ваш коллега написал вот такой код, но он почему-то не работает:
```cpp
#include "animals.h"

#include <iostream>
#include <stdexcept>
#include <vector>

using Zoo = std::vector<Animal>;

Zoo CreateZoo() {
    Zoo zoo;
    std::string word;
    while (std::cin >> word) {
        if (word == "Tiger") {
            Tiger t;
            zoo.push_back(t);
        } else if (word == "Wolf") {
            Wolf w;
            zoo.push_back(w);
        } else if (word == "Fox") {
            Fox f;
            zoo.push_back(f);
        } else
            throw std::runtime_error("Unknown animal!");
    }
    return zoo;
}

void Process(const Zoo& zoo) {
    for (const auto& animal : zoo) {
        std::cout << animal.voice() << "\n";
    }
}
```
Исправьте его и сдайте в систему.

Код классов из файла `animals.h` переписывать не надо, просто подключите заголовочный файл `animals.h`.
Обратите внимание, что в нашей версии файла `animals.h` голоса зверей могут отличаться от того, что приведено в примере.
Разумеется, в вашей программе не должно быть утечек памяти.
Экземпляр каждого зверя надо создавать ровно один раз (если вам на входе даны два волка, то надо создать ровно два объекта типа `Wolf`, не больше и не меньше).

### Решение

Давайте поймём, почему использовать `std::vector<Animal>` в качестве `Zoo` неправильно.
Вектор хранит копии элементов, которые мы туда кладём.
Эти копии будут иметь базовый тип `Animal` и ничего не будут знать про исходный тип объекта.
Поэтому в конструкции
```cpp
Tiger t;
zoo.push_back(t);
```
будет взята так называемая *срезка*: от тигра скопируется только подобъект базового класса `Animal`.
Конечно же, вызов `voice` для таких элементов вектора приведёт к вызову функции `Animal::voice`, которая напечатает `Not implemented yet`.

Использовать вектор ссылок нельзя, так как ссылка с самого начала должна быть к чему-то привязана.
Можно воспользоваться вектором указателей на `Animal` и создавать объекты в динамической памяти.
Но тогда придётся вручную следить за их временем жизни.
Самым правильным вариантом было бы создать вектор умных указателей `std::unique_ptr<Animal>`:
при уничтожении самого вектора автоматически вызвались бы деструкторы для его элементов, которые освободили бы занимаемую динамическую память.
Для создания нового объекта в динамической памяти и оборачивания указателя на него в `unique_ptr` удобно использовать функцию [`make_unique`](https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique):

```cpp
#include "animals.h"

#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using Zoo = std::vector<std::unique_ptr<Animal>>;

Zoo CreateZoo() {
    Zoo zoo;
    std::string word;
    while (std::cin >> word) {
        if (word == "Tiger") {
            zoo.push_back(std::make_unique<Tiger>());
        } else if (word == "Wolf") {
            zoo.push_back(std::make_unique<Wolf>());
        } else if (word == "Fox") {
            zoo.push_back(std::make_unique<Fox>());
        } else {
            throw std::runtime_error("Unknown animal!");
        }
    }
    return zoo;
}

void Process(const Zoo& zoo) {
    for (const auto& animal : zoo) {
        std::cout << animal->voice() << "\n";
    }
}
```