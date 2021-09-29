## Разбор задачи «Сериализация контейнеров»

### Условие

Вам нужно написать функции для бинарной сериализации и десериализации (то есть, записи/чтения в поток) примитивных типов, строк,
а также контейнеров `std::vector` и `std::map`, шаблонные параметры которых - типы такого же вида.
Например, ваша функция должна уметь сериализовать контейнер `std::vector<std::map<int, std::string>>`.
Заголовки функций, которые вам надо написать, представлены здесь:
```cpp
#include <map>
#include <iostream>
#include <string>
#include <vector>

// Для простых примитивных типов (int, bool, char и т. д.) и plain old data
template <typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);


template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);
```

Формат сериализации контейнеров должен быть таким: сначала записывается число типа `size_t` - размер контейнера, а затем уже сами элементы.
Для `std::map` записывайте элементы как пары, состоящие из ключа и значения.
Функции `Deserialize` должны восстанавливать исходный объект по сериализованному представлению.

Пусть, например, требуется сериализовать
```cpp
std::map<uint32_t, std::string> m = { {1, "hello"}, {2, "bye"} };
```
На 64-битной платформе с порядком байт little-endian результат должен получиться [таким](https://clck.ru/CWH6A) (тут показан вывод утилиты hd, применённый к полученному бинарному файлу).

Для простоты в этой задаче не нужно учитывать выравнивание (alignment) и можно считать, что порядок байт (endianness) при сериализации и десериализации будет одинаковым.
Используйте для записи и чтения байтов функции [`write`](http://en.cppreference.com/w/cpp/io/basic_ostream/write)
и [`read`](http://en.cppreference.com/w/cpp/io/basic_istream/read) у потоков типа `std::ostream` и `std::istream`.

### Решение
```cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out) {
    Serialize(str.size(), out);
    out.write(reinterpret_cast<const char*>(str.data()), str.size());
}

// пишем forward-декларацию, чтобы вызовы Serialize из последующих функций знали об этой специализации
template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (const auto& elem : data) {
        Serialize(elem, out);
    }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (const auto& pair : data) {
        Serialize(pair.first, out);
        Serialize(pair.second, out);
    }
}

template <typename T>
void Deserialize(std::istream& in, T& pod) {
    in.read(reinterpret_cast<char*>(&pod), sizeof(pod));
}

void Deserialize(std::istream& in, std::string& str) {
    size_t size;
    Deserialize(in, size);
    str.resize(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(&str[0]), size);
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
    size_t size;
    Deserialize(in, size);
    data.clear();
    data.reserve(size);
    for (size_t i = 0; i != size; ++i) {
        T elem;
        Deserialize(in, elem);
        data.push_back(std::move(elem));
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
    size_t size;
    Deserialize(in, size);
    data.clear();
    for (size_t i = 0; i != size; ++i) {
        T1 first;
        Deserialize(in, first);
        T2 second;
        Deserialize(in, second);
        data[std::move(first)] = std::move(second);
    }
}
```

Имя `pod` в первой функции происходит от сокращения "plain old data" - так раньше называли примитивные типы.

Здесь важно написать forward-декларации шаблонных функций для `map` перед функциями для `vector`,
чтобы вызовы `Serialize` и `Deserialize` для элементов вектора знали о такой специализации.

Обратите внимание, что содержимое строк можно сериализовать сразу, так как символы лежат в памяти подряд непрерывным куском.
С вектором такой трюк получился бы только для примитивных типов. Но сложные типы должны сериализоваться поэлементно.