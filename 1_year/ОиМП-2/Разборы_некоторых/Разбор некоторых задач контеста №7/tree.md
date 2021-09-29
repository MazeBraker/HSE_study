## Разбор задачи «Tree»

### Условие
Вася пишет новую структуру данных — дерево.
В узлах и листьях дерева хранятся строковые ключи.
Каждый путь от корня до какого-нибудь узла можно записать, перечисляя последовательные ключи узлов.
Типичный пример — иерархия папок в файловой системе.
Вася уже выбрал способ хранения дерева:
```cpp
#include <map>
#include <string>
#include <vector>

struct Node {
    std::map<std::string, Node> children;
};

class Tree {
private:
    Node root;

public:
    bool Has(const std::vector<std::string>& node) const;
    void Insert(const std::vector<std::string>& node);
    void Delete(const std::vector<std::string>& node);
};

// Ваш код будет вставлен сюда
#include "your_code"
```
Не будем обсуждать, насколько это эффективно.
Ваша задача — написать реализации функций `Has`, `Insert` и `Delete` для этого класса.
В примере с папками в файловой системе функция `Has` должна проверить, существует ли такая папка,
функция `Insert` должна создать папку (возможно, с промежуточными родительскими папками),
а `Delete` — удалить папку со всеми вложенными подпапками, если такая папка существует.

Можно считать, что вектор, передаваемый на вход этих функций, всегда непустой.

### Решение
Рассмотрим для начала функцию `Has`.
Её канва должна выглядеть так:
```cpp
bool Tree::Has(const std::vector<std::string>& node) const {
    // заводим переменную current, "смотрящую" на корень дерева
    for (const auto& item : node) {
        if (/* среди потомков current есть item */) {
            // заменить current на этого потомка
        } else {
            return false;
        }
    }
    return true;
}
```
Какого типа может быть `current`?
Правильный ответ: это должен быть указатель на `Node`.
При спуске по дереву его можно будет переназначать на вложенный узел:
```cpp
bool Tree::Has(const std::vector<std::string>& node) const {
    const Node * current = &root;
    for (const auto& item : node) {
        if (current->children.count(item) == 0) {
            return false;
        }
        current = &current->children.at(item);
    }
    return true;
}
```
Мы здесь используем `const Node *`, потому что функция `Has` константная, а значит, поле `root` тоже рассматривается как константное.
По этой же причине мы пишем `children.at(item)`, а не `children[item]`: оператор `[]` у `map` не является константным и его не получится использовать.
Вместо `children.count(item)` можно было бы взять `children.find(item)` и сравнить полученный итератор с `children.end()`.

Теперь напишем `Insert`:
```cpp
void Tree::Insert(const std::vector<std::string>& node) {
    Node * current = &root;
    for (const auto& item : node) {
        if (current->children.count(item) == 0) {
            current->children[item];  // просто вставляем новый ключ с пустым Node в качестве значения
        }
        current = &current->children.at(item);
    }
}
```

В функции `Delete` нам не нужно спускаться на самый последний узел: вместо этого его имя надо будет удалить из предпоследнего узла.
Поэтому воспользуемся индексами для итерации по списку промежуточных узлов `node`:
```cpp
void Tree::Delete(const std::vector<std::string>& node) {
    Node * current = &root;
    for (size_t i = 0; i < node.size(); ++i) {
        const auto& item = node[i];
        if (current->children.count(item) == 0) {
            return;
        }
        if (i + 1 == node.size()) {
            current->children.erase(item);
        } else {
            current = &current->children.at(item);
        }
    }
}
```
Грубая ошибка в функции `Delete` — пытаться написать `delete current` для удаления узла. Мы хотя и работаем с указателями, но оператор `delete` можно применять лишь к указателю на данные, выделенные с помощью `new`. Нам же нужно просто удалить значение с указанным ключом из контейнера `map`.

Другая грубая ошибка в этой задаче — пытаться использовать `Node current` вместо указателя.
Смотрите, вот такой `Has` на первый взгляд даже будет работать:
```cpp
bool Tree::Has(const std::vector<std::string>& node) const {
    Node current = root;
    for (const auto& item : node) {
        if (current.children.count(item) == 0) {
            return false;
        }
        current = current.children.at(item);
    }
    return true;
}
```
Однако можно заметить, что здесь на каждой итерации происходит полное копирование поддерева.
(В этом можно убедиться, если определить для `struct Node` конструктор копирования, печатающий сообщения на экран.)
Конечно же, при навигации по дереву никаких лишних копирований происходить не должно.
Более того, из-за особенностей внутренней реализации `std::map` выражение `current = current.children.at(item)` приведет к неопределенному поведению программы (родительское дерево будет разрушено до обращения к поддереву).