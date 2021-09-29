## Разбор задачи LoggerGuard

### Условие
Вася хочет иметь возможность в конце работы своей функции выводить сообщение, что функция завершила работу.
На практике исполнение функции может завершиться разными способами:
* Может быть несколько операторов `return`.
* Может вылететь исключение из какой-нибудь вызываемой функции.
С учетом этих обстоятельств у Василия получается раздутый код:
```cpp
#include <iostream>

int Function() {
  int value = 1;
  try {
    int value = SomeAnotherFunction();
    if (value == 0) {
      std::cout << "Function completed\n";
      return value;
    }

    value = SomeSecondFunction();
    if (value == 0) {
      std::cout << "Function completed\n";
      return value;
    }

    value = FinalFunction();  // might throw an exception
  } catch (...) {
    std::cout << "Function completed\n";
    throw;  // throws the exception further.
  }

  std::cout << "Function completed\n";
  return value;
}
```

Вместо этого Василий хотел бы не заниматься копированием одного и тоже же кода.
Помогите Василию и реализуйте класс `LoggerGuard`, который принимает строку и печатает ее во время выхода из функции.
С использованием этого класса код Василия станет таким:
```cpp
#include <iostream>

int Function() {
  LoggerGuard logger("Function completed");

  int value = 1;
  try {
    int value = SomeAnotherFunction();
    if (value == 0) {
      return value;
    }

    value = SomeSecondFunction();
    if (value == 0) {
      return value;
    }

    value = FinalFunction();  // might throw an exception
  } catch (...) {
    throw;  // throws the exception further.
  }

  return value;
}
```

Класс `LoggerGuard` должен содержать следующий конструктор:
```cpp
LoggerGuard(const std::string& message, std::ostream& out = std::cout);
```
Здесь `message` — сообщение, печатаемое перед выходом из функции, а `out` — поток, в который надо печатать сообщение.
Учтите, что это сообщение не обязано содержать символ перевода строки и вам нужно всегда при выводе самим добавлять `\n` в конце.


### Решение

`LoggerGuard` должен быть классом, в конструкторе которого запоминается сообщение и поток, а в деструкторе оно печатается.
Тогда для печати сообщения при любом выходе из функции достаточно будет создать локальную переменную типа `LoggerGuard`.
Как бы мы ни покинули функцию, её деструктор будет вызван автоматически.
Эта идея повсеместно используется в C++.

```cpp
#include <iostream>
#include <string>

class LoggerGuard {
private:
    std::string Message;
    std::ostream& Out;
public:
    LoggerGuard(const std::string& message, std::ostream& out = std::cout):
        Message(message),
        Out(out)
    {
    }

    ~LoggerGuard() {
        Out << Message << "\n";
    }
};
```

Мы не можем скопировать поток вывода в новую переменную (у класса `std::ostream` нет конструктора копирования).
Для этого мы запоминаем поток по ссылке. Так как ссылка должна быть сразу же проинициализирована при создании объекта, то мы пользуемся специальным синтаксисом для инициализации полей класса до входа в тело конструктора.

Другой способ - хранить в классе указатель на поток:
```cpp
#include <iostream>
#include <string>

class LoggerGuard {
private:
    std::string Message;
    std::ostream* Out;
public:
    LoggerGuard(const std::string& message, std::ostream& out = std::cout) {
        Message = message;
        Out = &out;
    }

    ~LoggerGuard() {
        *Out << Message << "\n";
    }
};
```