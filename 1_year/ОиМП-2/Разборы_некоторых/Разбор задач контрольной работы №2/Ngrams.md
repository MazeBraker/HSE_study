## Разбор задачи "Символьные N-граммы"

### Условие
N-граммой символов текста называется последовательность из N последовательно идущих символов в одном слове в тексте.
Для данного числа N подсчитайте суммарное количество каждой N-граммы в тексте.

В первой строке заданы два числа: M - число слов в тексте (от 1 до 100000) и N - длина N-граммы (от 1 до 5).
Далее (возможно, на разных строках) идет M слов. Можно считать, что слова отделены пробелами или переносами строк; обработку пунктуации и регистра реализовывать не нужно.
Читайте слова просто через `std::cin >> word`.

Выведите все N-граммы, отсортированные по убыванию частоты, а в случае равных частот — лексикографически (по алфавиту). Для каждой N-граммы напечатайте также ее частоту.


### Решение
Задача похожа на классическую задачу про подсчёт частоты слов из [лекций](https://gist.github.com/alzobnin/a96764dd8a0d8e6384245944c46f1ece),
только вместо слов надо будет подсчитывать подстроки слов длины N.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    size_t m, n;
    std::cin >> m >> n;

    std::unordered_map<std::string, int> freqs;

    for (size_t i = 0; i != m; ++i) {
        std::string word;
        std::cin >> word;
        for (size_t j = n; j <= word.size(); ++j) {
            ++freqs[word.substr(j - n, n)];
        }
    }

    std::vector<std::pair<std::string, int>> sorted(freqs.begin(), freqs.end());
    std::sort(
        sorted.begin(),
        sorted.end(),
        [](const auto& p1, const auto& p2) {
            return std::tie(p2.second, p1.first) < std::tie(p1.second, p2.first);
        }
    );

    for (const auto& [word, freq] : sorted) {
        std::cout << word << " - " << freq << "\n";
    }
}
```

Пожалуй, самый нетривиальный фрагмент здесь по сравнению с тем, что разобрано в конспекте лекции, - выделение подстрок:
```cpp
   for (size_t j = n; j <= word.size(); ++j) {
        ++freqs[word.substr(j - n, n)];
    }
```
Здесь `j` пробегает все позиции *за* последним символом подстроки.
Соотвественно, `j-n` - всевозможные начальные позиции подстрок длины `n`.
Так организованный цикл защищён от случайных переполнений и вычитаний большего числа из меньшего в беззнаковом типе `size_t`.
В таких конструкциях всегда полезно проверять себя на "крайних" случаях (например, когда `n` совпадает с `word.size`).


Если известно, что N мало по сравнению со средним размером слова, то более выгодным по скорости может оказаться другое решение:
сначала сохраняем в `unordered_map` все слова, а сами N-граммы строим как `unordered_map<string_view, int>`:

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    size_t m, n;
    std::cin >> m >> n;

    std::unordered_map<std::string, int> words;
    words.reserve(m);
    for (size_t i = 0; i != m; ++i) {
        std::string word;
        std::cin >> word;
        ++words[word];
    }

    std::unordered_map<std::string_view, int> freqs;

    for (const auto& [word, freq] : words) {
        std::string_view sv = word;
        for (size_t j = n; j <= sv.size(); ++j) {
            freqs[sv.substr(j - n, n)] += freq;
        }
    }

    std::vector<std::pair<std::string_view, int>> sorted(freqs.begin(), freqs.end());
    std::sort(
        sorted.begin(),
        sorted.end(),
        [](const auto& p1, const auto& p2) {
            return std::tie(p2.second, p1.first) < std::tie(p1.second, p2.first);
        }
    );

    for (const auto& [word, freq] : sorted) {
        std::cout << word << " - " << freq << "\n";
    }
}
```


### Неверные решения

Одно из поступивших неверных решений содержало ошибочный компаратор пар:
```cpp
bool comparator(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    if (a.second > b.second) {
        return true;
    }
    if (a.first < b.first) {
        return true;
    }
    return false;
}
```
Разберитесь-ка, в чём тут дело.