## Разбор задачи «Retry»

### Условие
Иногда некоторые действия не получается выполнить с первого раза.
Например, обращение по сети в сторонний сервис может обернуться неудачей из-за сетевых проблем или перегрузки сервиса.
В таких случаях иногда пишут код, пытающийся повторить такое действие несколько раз подряд.

Вам надо написать реализацию функции `DoWithRetry` с таким заголовком:
```cpp
#include <exception>
#include <functional>
#include <optional>

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(std::function<Result()> func, int retryCount, int sleepTime, bool throwLast);
```
Функция принимает на вход другую функцию без аргументов, возвращающую значение типа `Result`, количество повторов, таймаут между повторами и флажок `throwLast`.
Одним из шаблонных параметров функции является тип исключения, на которое функция реагирует.
Функция должна вызвать `func`, и если произошло исключение указанного типа, то вызвать нашу функцию `Sleep` с параметром `sleepTime`, а затем повторить попытку (если попытки еще остались).
Максимальное количество вызовов `func`, которое может получиться, равно `retryCount + 1`.
Если на последней попытке происходит исключение указанного типа, и `throwLast` истинно, этот же объект исключения должен проброситься дальше из функции.
Если же `throwLast` ложно, то надо просто вернуть пустой объект `std::optional`.
Если же вызов `func` закончился успешно, то надо просто вернуть результат `func`.

Про `std::optional` можно прочитать [здесь](https://en.cppreference.com/w/cpp/utility/optional).
Если исключение произошло на последней попытке, то после нее "спать" не надо.

### Решение
```cpp
#include <exception>
#include <functional>
#include <optional>

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(std::function<Result()> func, int retryCount, int sleepTime, bool throwLast) {
    for (int i = 0; i < retryCount + 1; ++i) {
        try {
            return func();
        } catch (const Exception&) {
            if (i == retryCount) {
                if (throwLast) {
                    throw;
                } else {
                    return {};
                }
            } else {
                Sleep(sleepTime);
            }
        }
    }
    return {};
}
```
Здесь мы перехватываем потенциальные исключения, приводящиеся к типу `Exception` (важно ловить именно их, а не писать `catch (...)`).
При этом сам объект исключения нам не нужен, поэтому мы его имя не указываем.
При необходимости (после последней попытки при возведенном `throwLast`) мы перекидываем пойманное исключение дальше с помощью `throw` без аргументов