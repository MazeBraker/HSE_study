## Разбор задачи Deque

### Условие
В этой задаче вам надо будет написать свой дек.
Писать его по-честному долго и сложно, поэтому мы пошли вам навстречу: вам нужно написать упрощенную версию дека без итераторов, и умеющую только добавлять элементы в начале и в конце.
Поддерживать удаление элементов из дека не требуется.
В отличие от стандартного дека возьмите за основу два вектора, растущих каждый в свою сторону.
Возьмите за основу вот такой прототип и реализуйте указанные функции:
```cpp
#include <cstddef>
#include <vector>

template <typename T>
class Deque {
private:
  std::vector<T> head, tail;

public:
  bool Empty() const;

  size_t Size() const;

  void Clear();

  const T& operator [] (size_t i) const;

  T& operator [] (size_t i);

  const T& At(size_t i) const;  // throws std::out_of_range on incorrect index

  T& At(size_t i);  // throws std::out_of_range on incorrect index

  const T& Front() const;

  T& Front();

  const T& Back() const;

  T& Back();

  void PushFront(const T& elem);

  void PushBack(const T& elem);
};
```
Сдайте в систему класс `Deque` с написанными функциями.

### Решение
Дек должен уметь эффективно расти в обе стороны.
А вектор умеет эффективно расти только в одну сторону.
Поэтому предлагается реализовать решение с помощью двух векторов, смотрящих в разные стороны.
По условию удаляться из дека ничего не будет, поэтому в эти векторы будут только добавляться новые элементы в конец.
Однако важно помнить, что один из этих векторов может оставаться пустым, если с соответствующей стороны вставок еще не было.
Поэтому, например, при вызовe `Front` мы должны сначала посмотреть на первый вектор, а если он пуст - то на второй.

### Часто задаваемые вопросы
**Q.** _Какой из векторов (`head` или `tail`) соотвествует началу, а какой - концу дека?_\
**A.** На самом деле это детали нашей реализации, никак не связанные с объявленным публичным интерфейсом, который требуется реализовать.
Можно выбрать любое соответствие и придерживаться его.

**Q.** _Какой должен быть конструктор дека? Нужен ли конструктор от двух векторов?_\
**A.** Заметим, что в представленном публичном интерфейсе конструктора нет. Значит, компилятор предоставит по умолчанию конструктор без аргументов, инициализирующий поля `head` и `tail` их дефолтными конструкторами. Конечно, такой конструктор создаёт пустой дек. Другие конструкторы не требуются. Итак, конструктор можно вообще не писать - нам достаточно дефолтного.

**Q.** _Что должны делать функции Front и Back на пустом деке?_\
**A.** Как и в `std::deque`, они не должны делать никаких проверок. То, что эти функции не вызываются на пустом деке, лежит на совести программиста.

**Q.** _Что должна делать функция At?_\
**A.** Как и в контейнерах стандартной библиотеки, она аналогична оператору `[]`, но проверяет корректность индекса.
В случае некорректного индекса она должна генерировать исключение.

**Q.** _Не получается сгенерировать исключение._\
**A.** Во-первых, надо подключить `<stdexcept>` - этот заголовочный файл указан в документации `std::out_of_range`.
В конструктор `std::out_of_range` надо передать текстовую строку с описанием ошибки.
Строка может быть любой, мы её не проверяем.

### Ответ
```cpp
#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T>
class Deque {
private:
  std::vector<T> head, tail;

  void CheckIndex(size_t i) const {
    if (i >= Size()) {
      throw out_of_range("Index is out of range");
    }
  }

public:
  bool Empty() const {
    return head.empty() && tail.empty();
  }

  size_t Size() const {
    return head.size() + tail.size();
  }

  void Clear() {
    head.clear();
    tail.clear();
  }

  const T& operator [] (size_t i) const {
    return i < head.size() ? head[head.size() - i - 1] : tail[i - head.size()];
  }

  T& operator [] (size_t i) {
    return i < head.size() ? head[head.size() - i - 1] : tail[i - head.size()];
  }

  const T& At(size_t i) const {
    CheckIndex(i);
    return (*this)[i];
  }

  T& At(size_t i) {
    CheckIndex(i);
    return (*this)[i];
  }

  const T& Front() const {
    return head.empty() ? tail.front() : head.back();
  }

  T& Front() {
    return head.empty() ? tail.front() : head.back();
  }

  const T& Back() const {
    return tail.empty() ? head.front() : tail.back();
  }

  T& Back() {
    return tail.empty() ? head.front() : tail.back();
  }

  void PushFront(const T& elem) {
    head.push_back(elem);
  }

  void PushBack(const T& elem) {
    tail.push_back(elem);
  }
};
```