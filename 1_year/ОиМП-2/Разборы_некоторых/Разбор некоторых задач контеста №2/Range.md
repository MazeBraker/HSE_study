## Разбор задачи Range

### Условие
Реализуйте функцию с заголовком
```cpp
std::vector<int> Range(const std::vector<int>& v, size_t start, size_t end, size_t step = 1);
```

Данная функция принимает вектор чисел и возвращает новый вектор, которые составлен из элементов
данного вектора начиная с индекса start и заканчивая индексом end не включительно
с шагом step. В случае, если подходящих для ответа элементов нет, функция должна просто вернуть пустой вектор.

Гарантируется, что `step` не равен нулю, и больше никаких гарантий не дается.


### Решение
Сначала необходимо определиться с тем, как работает смещение `step`. Смещение может только сдвинуть
нашу текущую позицию вправо в сторону увеличения индексов, т. к. `step` имеет тип size_t (т. е. неотрицательное число)
и гарантируется, что `step` не равен нулю и мы не будет топтаться на одном месте.

В условии указано, что больше никаких гарантий не дается. Это означает, что нужно обдумать
узкие кейсы самых разных вариантов некорректных входов.

Примеры:
1) Пустой вектор. Здесь нужно вернуть пустой вектор.
2) start == end. Здесь нужно вернуть пустой вектор, т. к. нужно выводить до end не включительно.
3) start > end. Здесь нужно вернуть пустой вектор, т. к. формально промежуток [start, end) является пустым.
4) end > v.size(). Здесь необходимо ничего не возвращать из индексов [v.size, end), т. к. там нет никаких данных.

Из данного понимания можно необдумано с первого раза написать следующее неправильное решение:
```cpp
std::vector<int> Range(const std::vector<int>& v, size_t start, size_t end, size_t step = 1) {
    std::vector<int> data;
    end = std::min(end, v.size());
    if (start >= end)
        return data;

    while (start < end) {
        data.push_back(v[start]);
        start += step;
    }

    return data;
}

```

Остается проблема в строчке `start += step;`. Т. к. аргументы могут поступить в функцию любые, может произойти такое, что
число `start` переполнится (что разрешено в С++ для беззнаковых чисел) и условие `start < end` выполнится и цикл может продолжить
добавлять какие-то данные. Хотя формально нужно в таком случае завершать работу, т. к. определение работы функции в условии
сформулированно на человеческом языке, в котором по умолчанию не делается предположений, что какие-то беззнаковые числа
переполняются по модулю `2^64 - 1`.

Учитывая это обстоятельство, правильное решение может выглядеть так.
```cpp
std::vector<int> Range(const std::vector<int>& v, size_t start, size_t end, size_t step = 1) {
    std::vector<int> data;
    end = std::min(end, v.size());
    if (start >= end)
        return data;

    while (true) {
        data.push_back(v[start]);
        if (end - start <= step)
            break;

        start += step;
    }

    return data;
}

```

Новая проверка `end - start <= step` не использует переполнений и проверяет, что расстояние до конца массива не превышает шаг,
который мы собираемся сделать. Потому и условие в операторе `while` становится необязательным.