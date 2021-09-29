## Разбор задачи «BiMap»

### Условие
Все вы знаете контейнер `std::map`, который сопоставляет уникальным ключам значение.
Представим теперь, что мы работаем с данными, у которых бывает два типа ключей.
Например, студента можно задать номером студенческого билета или логином в системе.
При этом не обязательно заданы оба ключа: например, у студента может ещё не быть логина.

Вам надо написать класс `BiMap`, к которому можно обратиться за значением по одному из двух типов ключей.
Вот заготовка для вашего класса:
```cpp
#include <stdexcept>
#include <optional>

template <typename Key1, typename Key2, typename Value>
class BiMap {
public:
    // Вставить значение, указав один или оба ключа.
    // Генерирует исключение std::invalid_argument("some text") в случае,
    // если оба ключа пусты, либо один из ключей уже имеется в хранилище.
    void Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2, const Value& value);

    // Получить значение по ключу первого типа.
    // Генерирует исключение std::out_of_range("some text")
    // в случае отсутствия ключа (как и функция at в std::map).
    Value& GetByPrimaryKey(const Key1& key);
    const Value& GetByPrimaryKey(const Key1& key) const;

    // Аналогичная функция для ключа второго типа.
    Value& GetBySecondaryKey(const Key2& key);
    const Value& GetBySecondaryKey(const Key2& key) const;
};
```
Функция `Insert` пытается вставить новое значение в хранилище.
Ей могут быть указаны какой-то один или оба ключа (поэтому ключи передаются через `std::optional`).
Если оба ключа не заданы, или если один из ключей уже есть в хранилище, функция должна сгенерировать исключение `std::invalid_argument` с каким-либо текстовым параметром.

Функции `GetByPrimaryKey` и `GetBySecondaryKey` должны вернуть значение по ключу соответствующего типа.
Они очень похожи на функцию `at` в `std::map`: в случае отстутствия ключа должна генерироваться ошибка `std::out_of_range`.

Вот пример тестовой программы, демонстрирующей работу этих функций:
```cpp
#include "bimap.h"

#include <iostream>
#include <string>

using namespace std;

struct Student {
    string Surname, Name;
};

ostream& operator << (ostream& out, const Student& s) {
    return out << s.Surname << " " << s.Name;
}

int main() {
    BiMap<int, string, Student> bimap;  // студента можно определить либо по номеру, либо по логину
    bimap.Insert(42, {}, {"Ivanov", "Ivan"});
    bimap.Insert({}, "cshse-ami-512", {"Petrov", "Petr"});
    bimap.Insert(13, "cshse-ami-999", {"Fedorov", "Fedor"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan

    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    bimap.GetByPrimaryKey(13).Name = "Oleg";  // меняем значение по первичному ключу - по вторичному оно тоже должно измениться
    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg
    return 0;
}
```

Вы можете воспользоваться контейнером `std::map` для реализации класса (в частности, можно считать, что на ключах определён operator `<`).

Сдайте в систему только код класса `BiMap` без функции `main`. Подключите все необходимые для вашей реализации библиотеки.


### Решение
Давайте заметим, что вот такое решение нам не подойдёт:
```cpp
template <typename Key1, typename Key2, typename Value>
class BiMap {
    std::map<Key1, Value> map1;
    std::map<Key2, Value> map2;
};
```
В этом решении значения в `map1` и `map2` никак не зависят друг от друга.
Если мы обратимся к значению по первому ключу и поменяем его, а потом прочитаем значение по второму ключу, то мы не увидим изменений.

Поэтому нужно, чтобы значения хранились где-то отдельно в одном экземпляре, а отображения из ключей ссылались бы на них.
Например, можно сохранять значения в контейнере, а ключи отображать в индексы:
```cpp
template <typename Key1, typename Key2, typename Value>
class BiMap {
    std::deque<Value> values;
    std::map<Key1, size_t> map1;
    std::map<Key2, size_t> map2;
};
```
Индексы можно было бы заменить на итераторы, если выбраны контейнеры `deque` или `list`, но для контейнера `vector` итераторы использовать не получится: при добавлении новых элементов в вектор может произойти реаллокация, и старые итераторы будут инвалидированы.

Другое решение не использует отдельного хранилища значений.
Вместо этого значения создаются в динамической памяти.
Чтобы не думать о том, кто и в какой момент должен освобождать эту память, можно обернуть их в умный указатель.
Так как на значение может быть две ссылки, то нужно использовать умный указатель `shared_ptr`.
Рассмотрим это решение подробнее.
```cpp
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>

template <typename Key1, typename Key2, typename Value>
class BiMap {
private:
    std::map<Key1, std::shared_ptr<Value>> map1;
    std::map<Key2, std::shared_ptr<Value>> map2;

public:
    void Insert(
        const std::optional<Key1>& key1,
        const std::optional<Key2>& key2,
        const Value& value
    ) {
        if (!key1.has_value() && !key2.has_value()) {
            throw std::invalid_argument("Both keys are empty");
        }
        auto shared = std::make_shared<Value>(value);
        if (key1.has_value()) {
            if (map1.find(*key1) != map1.end()) {
                throw std::invalid_argument("Key already exists");
            }
            map1[*key1] = shared;
        }
        if (key2.has_value()) {
            if (map2.find(*key2) != map2.end()) {
                throw std::invalid_argument("Key already exists");
            }
            map2[*key2] = shared;
        }
    }

    Value& GetByPrimaryKey(const Key1& key) {
        return *map1.at(key);
    }

    const Value& GetByPrimaryKey(const Key1& key) const {
        return *map1.at(key);
    }

    Value& GetBySecondaryKey(const Key2& key) {
        return *map2.at(key);
    }

    const Value& GetBySecondaryKey(const Key2& key) const {
        return *map2.at(key);
    }
};
```
Здесь вместо `if (key.has_value())` можно было бы просто написать [`if (key)`](https://en.cppreference.com/w/cpp/utility/optional/operator_bool).
В `Get`-функциях мы не проверяем наличие ключа: при его отсутствии вызываемая функция `at` сама сгенерирует исключение нужного типа.
