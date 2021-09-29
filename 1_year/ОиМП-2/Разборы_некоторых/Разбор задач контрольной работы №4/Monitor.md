## Разбор задачи «Монитор»

### Условие
Вася разрабатывает новую систему для проведения контестов по программированию.
Ему поручено разработать класс `Monitor`, хранящий результаты студентов в контесте по каждой задаче.
Этот класс должен уметь очень быстро возвращать текущие результаты и отдельного студента, и целой группы, и всего потока -
ведь следить за финальным контестом первокурсников будет весь ФКН, и на сервис будет приходить большая нагрузка.
Каждый может наблюдать в мониторе только за интересующим его срезом - например, только за одной группой.


Васе уже дан готовый класс `StudentResults`, описывающий результаты одного студента:
```cpp
#include <map>
#include <string>

struct StudentResults {
    std::string login;
    std::string group;
    std::map<std::string, int> scores;  // номер задачи -> баллы

    // ...

    StudentResults(const std::string& l, const std::string& gr): login(l), group(gr) {
    }

    StudentResults(const StudentResults&) = delete;
    StudentResults& operator=(const StudentResults&) = delete;
};
```
Его изменить вы не можете. Класс может быть "тяжелым" в инициализации и копировании.
Чтобы не создавались лишние копии этого класса, его конструктор копирования и оператор присваивания вообще удалены.

В классе `Monitor`, который пишет Вася, должны быть следующие функции:

1. `RegisterStudent(const std::string& login, const std::string& group)` -
регистрирует студента в указанной группе и возвращает (в каком-то виде) созданный для него `StudentResults`.
Если студент с таким логином уже зарегистрирован, то выбрасывает исключение `std::invalid_argument`.

2. `GetStudentResults(const std::string& login)` - получает (в каком-то виде) `StudentResults` для данного студента.
Если такого логина нет, выкидывает `std::out_of_range`.
Должна быть константная версия (для отрисовки результатов) и неконстантная (для обновлений результатов после очередной посылки).

3. `GetGroupResults(const std::string& group) const` - возвращает (в каком-то виде) контейнер из `StudentResults` для данной группы.
Если такой группы нет, выкидывает `std::out_of_range`.

4. `GetAllResults() const` - возвращает (в каком-то виде) контейнер всех результатов.


Использоваться этот класс будет примерно так:
```cpp
#include "student_results.h"
#include "monitor.h"

#include <iostream>

int main() {
    Monitor monitor;

    {
        auto ptr = monitor.RegisterStudent("Ivanov Ivan", "201-1");
        ptr->scores["A"] = 10;
        ptr->scores["B"] = 8;
    }

    {
        auto ptr = monitor.RegisterStudent("Petrov Petr", "201-2");
        ptr->scores["A"] = 5;
        ptr->scores["C"] = 10;
    }

    auto ptr = monitor.GetStudentResults("Ivanov Ivan");
    ptr->scores["Z"] = 100;

    // тут может быть аналогичный вызов monitor.GetGroupResults(group)
    for (const auto& result : monitor.GetAllResults()) {
        std::cout << result->login << "\t" << result->group << "\t";
        for (const auto& [problemId, score] : result->scores) {
            std::cout << problemId << ": " << score << "\t";
        }
        std::cout << "\n";
    }
}
```

Вася решил, что будет хранить вектор указателей на результаты для каждой группы и для всего потока.
Указатели позволят ему сделать результаты "общими" в каждом из этих векторов и не составлять такие векторы заново при каждом вызове функций `GetByGroup` или `GetAllResults`. Вот заготовка Васи:
```cpp
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Monitor {
private:
    // удобные псевдонимы типов для краткости:
    using Ptr = StudentResults*;
    using ConstPtr = const StudentResults*;

    std::map<std::string, Ptr> by_student;
    std::map<std::string, std::vector<ConstPtr>> by_group;
    std::vector<ConstPtr> all_results;

public:
    Monitor() = default;
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    Ptr RegisterStudent(const std::string& login, const std::string& group) {
        if (by_student.contains(login)) {
            throw std::invalid_argument("Student is already registered");
        }
        // Добавить новую запись о студенте и вернуть ее
    }

    Ptr GetStudentResults(const std::string& login) {
        return by_student.at(login);
    }

    ConstPtr GetStudentResults(const std::string& login) const {
        return by_student.at(login);
    }

    std::vector<ConstPtr> GetGroupResults(const std::string& group) const {
        return by_group.at(group);
    }

    std::vector<ConstPtr> GetAllResults() const {
        return all_results;
    }
};
```

Сдайте свою версию класса `Monitor`.
Вам нужно дописать функцию `RegisterStudent` и, если потребуется, еще что-то.
Вы можете выбрать реализацию Васи, а можете заменить её на свою, если хотите.

В вашей программе не должно быть функции `main`.
Сдайте в систему только код класса `Monitor`.
Подключите необходимые заголовочные файлы.
Класс `StudentResults` подключать или объявлять не нужно: мы его подключим сами.

Напоминаем, что обычный указатель можно всегда передать туда, где ожидается указатель на константу, но не наоборот.


### Решение
Заметим сразу, что необходимые исключения из функций `GetStudentResults` и `GetGroupResults` и так уже пробрасываются:
при отсутствии ключа `std::map::at` сгенерирует исключение `std::out_of_range`. Поэтому никаких проверок тут дописывать не надо.


Самое простое решение - создавать объекты класса `StudentResults` в динамической памяти и класть в контейнеры указатели.
```cpp
Ptr RegisterStudent(const std::string& login, const std::string& group) {
    if (by_student.contains(login)) {
        throw std::invalid_argument("Student is already registered");
    }

    StudentResults* ptr = new StudentResults(login, group);
    all_results.push_back(ptr);
    by_student[login] = ptr;
    by_group[group].push_back(ptr);
}
```
При таком подходе получится утечка памяти, так как деструктор вектора `all_results` ничего не будет делать с голыми указателями.
Поэтому здесь необходимо реализовать ещё и свой собственный деструктор:
```cpp
~Monitor() {
    for (auto ptr : all_results) {
        delete ptr;
    }
}
```

---

Более правильное и безопасное решение - использовать умные указатели.
Так как на один и тот же объект `StudentResults` мы будем ссылаться из разных мест, то `std::unique_ptr` нам не подойдёт, и нужно использовать `std::shared_ptr`.
Меняем псевдонимы типов `Ptr` и `ConstPtr`:
```cpp
using Ptr = std::shared_ptr<StudentResults>;
using ConstPtr = std::shared_ptr<const StudentResults>;
```
(важно не спутать умный указатель на константу и `const std::shared_ptr<StudentResults>`).


Дописываем функцию `RegisterStudent`:
```cpp
Ptr RegisterStudent(const std::string& login, const std::string& group) {
    if (by_student.contains(login)) {
        throw std::invalid_argument("Student is already registered");
    }

    Ptr ptr = std::make_shared<StudentResults>(login, group);
    all_results.push_back(ptr);
    by_student[login] = ptr;
    by_group[group].push_back(ptr);
    return ptr;
}
```
Всю работу по очистке памяти `shared_ptr` сделает за нас, поэтому деструктор тут не нужен.
Когда объект типа `Monitor` будет умирать, то будут автоматически вызваны деструкторы вектора и `map`'ов, каждый из которых позовёт деструктор для хранящихся там `shared_ptr`.
Деструктор `shared_ptr` будет уменьшать счётчик ссылок на объект, и когда этот счётчик дойдёт до нуля - автоматически вызовет `delete`.