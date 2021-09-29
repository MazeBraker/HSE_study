## Разбор задачи «Key-value storage»

### Условие
Вася разрабатывает свою структуру данных - Key-value-хранилище.
Эта структура данных должна хранить значение, ассоциированное с ключом, и она будет делать это суперэффективно.
Пока для простоты Вася выбрал за основу `std::unordered_map`, но потом он это переделает.

Какие операции должно поддерживать такое хранилище?
Правильно: вставка элемента, удаление элемента и поиск элемента.
Вася написал прототипы функций `insert`, `remove` и `find`, но функция `find` почему-то не работает.
Помогите Васе её исправить. Вот код Васи:
```cpp
#include <unordered_map>

template <typename Key, typename Value>
class KeyValueStorage {
private:
  std::unordered_map<Key, Value> data;

public:
  void insert(const Key& key, const Value& value) {
    data[key] = value;
  }

  void remove(const Key& key) {
    data.erase(key);
  }

  bool find(const Key& key, Value * const value = nullptr) const;
};


// Почему-то не работает...
//
//template <typename Key, typename Value>
//bool KeyValueStorage<Key, Value>::find(const Key& key, Value * const value) const {
//  auto it = std::find(data.begin(), data.end(), key);
//  auto val = *it;
//  if (value != nullptr)
//    value = &val;
//  return it != data.end();
//}


// Ваша реализация функции KeyValueStorage::find будет вставлена сюда:

#include "your_version_of_find.h"
```
Ваша версия функции `find` будет вставлена в конце этого кода.
Её заголовок должен быть таким же, как в закомментированной части.

Функция `find` по задумке должна возвращать `true`, если ключ был найден, и `false` в противном случае.
Если второй аргумент функции `find` отличен от `nullptr` и ключ найден, то функция должна записать найденное значение в тот объект, на который ссылается этот аргумент
(предполагается, что новая структура данных сможет быстро определять наличие ключа, но само значение будет извлекаться дорого, и делать это нужно лишь при необходимости).
Использовать эту функцию предполагается примерно так:
```cpp
#include "key_value_storage.h"

#include <string>

int main() {
  KeyValueStorage<std::string, int> kv;
  kv.insert("hello", 42);
  kv.insert("bye", -13);
  int value = 123;
  auto res = kv.find("wrong", &value);  // должно вернуться false, а value не должен меняться
  res = kv.find("bye", &value);  // должно вернуться true, в value должно быть -13
  res = kv.find("hello", nullptr);  // должно вернуться true
}
```

### Решение
Наш код будет вставлен после класса. Поэтому для описания тела функции нам потребуется написать шапку `template <typename Key, typename Value>`,
а имя функции предварить префиксом с именем класса - как в закомментированном примере.

```cpp
template <typename Key, typename Value>
bool KeyValueStorage<Key, Value>::find(const Key& key, Value * const value) const {
  auto it = data.find(key);
  if (it != data.end() && value != nullptr) {
    *value = it->second;
  }
  return it != data.end();
}
```

### Примечания
Разберём типичные ошибки:

1. Не надо пытаться использовать общий алгоритм `std::find` или `std::find_if`.
Нужно использовать встроенную функцию `find` контейнера `unordered_map`.
Во-первых, встроенный `find` будет работать быстрее (а `std::find` будет выполнять линейный поиск).
Во-вторых, `std::find` не предназначен для поиска по ключу. Он ищет в контейнере готовый образец, а значит, ему придётся передать пару из ключа и значения (которого мы не знаем).

2. Если значение не найдено, не надо ничего делать с `value`. Это можно понять по примеру использования. В этом случае надо просто вернуть `false`.

3. Неправильно писать `value = &it->second`. Сам указатель `value` мы поменять не сможем; мы лишь записываем найденное значение в ту ячейку памяти, на которую он указывает (если он не `nullptr`).
По условию мы предполагаем, что он в таком случае указывает на корректный существующий объект.