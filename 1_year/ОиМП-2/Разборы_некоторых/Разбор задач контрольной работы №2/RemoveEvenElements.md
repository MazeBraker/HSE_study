## Разбор задачи RemoveEvenElements

### Условие
Имеется следующая неправильная реализация функции, которая удаляет из множества чисел четные элементы:
```cpp
#include <cstdint>
#include <set>

void RemoveEvenElements(std::set<int64_t>& s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (*it % 2 == 0) {
            s.erase(it);
        }
    }
}
```

Найдите ошибку и сдайте исправленное решение.

Требование к решению: функция должна использовать `O(1)` дополнительной памяти.

### Решение
Проблема в приведенном коде в том, что при удалении элемента из множества соотвествующий ему итератор инвалидируется,
а он затем используется для получения итератора на следующий элемент в выражении `++it`.

Возможным решением может быть аккуратный переход на следующий итератор в случае удаления элемента из множества:
```cpp
#include <cstdint>
#include <iterator>
#include <set>

void RemoveEvenElements(std::set<int64_t>& s) {
    auto it = s.begin();
    while (it != s.end()) {
        auto next_it = std::next(it);
        if (*it % 2 == 0) {
            s.erase(it);
        }

        it = next_it;
    }
}
```
Ещё можно воспользоваться тем, что `s.erase` возвращает итератор на элемент, следующий за удалённым:
```cpp
#include <cstdint>
#include <set>

void RemoveEvenElements(std::set<int64_t>& s) {
    for (auto it = s.begin(); it != s.end(); ) {
        if (*it % 2 == 0) {
            it = s.erase(it);
        } else {
            ++it;
        }
    }
}
```

Другим более простым решением является использование новой функции стандартной библиотеки С++20 [std::erase_if](https://en.cppreference.com/w/cpp/container/set/erase_if)
```cpp
#include <cstdint>
#include <set>

void RemoveEvenElements(std::set<int64_t>& s) {
    std::erase_if(s, [](int64_t x) { return x % 2 == 0; });
}
```

### Неверные решения

1) Очевидное неверное решение - взять код из условия и сдать без исправлений. Такой код приводит к неопределенному поведению и ловится тестом с ub-санитайзером.
Так как неопределенное поведение не обязано выливаться в какие-либо ошибки при каждом запуске, то может оказаться так, что вы, запустив код локально, не увидите никаких ошибок.
Но ошибки могут возникнуть в произвольный момент неожиданно для вас, и нахождение в вашем коде ошибок с неопределенным поведением недопустимо.

2) Неочевидное неверное решение - попробовать избавиться от итераторов и работать со значениями напрямую.
```cpp
void RemoveEvenElements(std::set<int64_t>& s) {
    for (int e : s) {
        if (e % 2 == 0)
            s.erase(e);
    }
}
```
Хотя явных итераторов здесь не наблюдается, в действительности конструкция [range-based for](https://en.cppreference.com/w/cpp/language/range-for) разворачивается в обычный цикл с итераторами и уйти от проблемы здесь не удается.

3) Корректное, но не удовлетворительное решение - скопировать нечетные элементы в std::vector и в конце заменить `s` на `std::set<int64_t>(vec.begin(), vec.end())`. Выдает правильный ответ, но не оптимально по дополнительной памяти `O(N)` и в контесте получает вердикт `ML`.

4) Решение, которое не имеет шансов скомпилироваться, - использовать связку [s.erase](https://en.cppreference.com/w/cpp/container/set/erase) + [std::remove_if](https://en.cppreference.com/w/cpp/algorithm/remove).
 ```cpp
void RemoveEvenElements(std::set<int64_t>& s) {
    s.erase(std::remove_if(s.begin(), s.end(), [](int64_t x) { return x % 2 == 0; }), s.end());
}
```
Как указано в документации функции `std::remove_if` в секции `notes`:
```
These algorithms cannot be used with associative containers such as std::set and std::map because ForwardIt does not dereference to a MoveAssignable type (the keys in these containers are not modifiable).
```
В самом деле, поменять порядок элементов в `std::set` нельзя (так как элементы хранятся в бинарном дереве поиска), а `remove_if` пытается сделать именно это.
Таким образом, использование `std::remove_if` приводит к ошибке компиляции.