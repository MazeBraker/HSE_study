## Разбор задачи "Общий префикс строк"

### Условие
Напишите функцию `std::string CommonPrefix(const std::vector<std::string>& words)`,
вычисляющую наибольший общий префикс строк, переданных в векторе `words`.
Например, для пустого вектора нужно вернуть пустую строку, а для вектора из строк `apple`, `apricot` и `application` — строку `ap`.

В вашем решении должны быть только подключения необходимых библиотек и функция `CommonPrefix`.
В решении могут быть и ваши вспомогательные функции (если они вам нужны). Мы скомпилируем ваш код с нашей функцией `main`.

### Решение
Давайте напишем вспомогательную функцию, вычисляющую общий префикс двух строк.
Для этого будем идти по символам строк и проверять, равны ли они.
Важно не выйти за пределы строки.
```cpp
#include <string>
#include <vector>

std::string CommonPrefix(const std::string& a, const std::string& b) {
    size_t i = 0;
    while (i != a.size() && i != b.size() && a[i] == b[i]) {
        ++i;
    }
    return a.substr(0, i);
}
```

Теперь можно просто перебрать поданные на вход строки и вычислять на каждом шаге общий префикс у текущей строки и старого префикса:
```cpp
std::string CommonPrefix(const std::vector<std::string>& words) {
    if (words.empty()) {
        return {};
    }
    std::string prefix = words[0];
    for (size_t i = 1; i != words.size() && !prefix.empty(); ++i) {
        prefix = CommonPrefix(prefix, words[i]);
    }
    return prefix;
}
```
Здесь мы вызываем в цикле первую функцию `CommonPrefix`. Компилятор понимает какую из функций надо вызвать по типам аргументов (здесь передаётся не вектор строк, а две строки).

Недостаток этого решения в том, что мы много раз создаём новые строки (префиксы), хотя на самом деле все они являются подстроками первой строки.
Поэтому давайте перепишем первую функцию, чтобы она использовала `string_view`.
Во второй функции объявим `prefix` с явным типом `string_view`, а в конце вернём `std::string(prefix)`:
преобразование из `string_view` обратно в `string` надо описывать явно.
```cpp
#include <string>
#include <string_view>
#include <vector>

std::string_view CommonPrefix(const std::string_view a, const std::string_view b) {
    size_t i = 0;
    while (i != a.size() && i != b.size() && a[i] == b[i]) {
        ++i;
    }
    return a.substr(0, i);
}

std::string CommonPrefix(const std::vector<std::string>& words) {
    if (words.empty()) {
        return {};
    }
    std::string_view prefix = words[0];
    for (size_t i = 1; i != words.size() && !prefix.empty(); ++i) {
        prefix = CommonPrefix(prefix, words[i]);
    }
    return std::string(prefix);
}
```


### Решение с синхронным проходом
Рассмотрим альтернативное решение.
Будем одновременно идти по всем словам.
Для этого удобно сначала вычислить их минимальную длину, чтобы было проще проверять, когда пора остановиться.

```cpp
#include <algorithm>
#include <string>
#include <vector>

std::string CommonPrefix(const std::vector<std::string>& words) {
    if (words.empty()) {
        return {};
    }

    size_t min_len = words[0].size();
    for (const auto& word : words) {
        min_len = std::min(min_len, word.size());
    }

    for (size_t i = 0; i < min_len; ++i) {
        const char c = words[0][i];
        for (const auto& word : words) {
            if (word[i] != c) {
                return word.substr(0, i);
            }
        }
    }

    return words[0].substr(0, min_len);
}
```

По сравнению с попарным решением есть преимущество: время работы равно `O(|result| * num_words)`, в отличие от попарного `O(sum len of words)`
Но есть и недостаток: при очень большом количестве слов нам придется постоянно обращаться к разным участкам памяти, а это может затормозить работу.