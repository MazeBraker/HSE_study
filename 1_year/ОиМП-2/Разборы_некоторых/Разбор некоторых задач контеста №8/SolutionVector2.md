### Разбор задачи Vector-2

При реализации этого класса, я полагаюсь на то, что вы уже прочли и знаете условие. Если это не так, то с условием вы можете ознакомиться по [ссылке](https://gist.github.com/cdraugr/a07815fd61627bc7b20a85bebe6cfb50). Если говорить кратко - нам нужно реализовать шаблонный класс `Vector<T>`, который будет вести себя так же, как и `std::vector<T>`.

Изначально поговорим об общем. В векторе есть три поля: `data`, `size`, `capacity`, где `data` - указатель на память в которой мы храним `size` объектов типа `T`, но при этом, памяти выделено под `capacity` объектов.

Теперь давайте договоримся про то, что и как мы будем поддерживать на примере метода `resize`. Есть несколько вариантов реализации. Рассмотрим более "идейную" (на мой взгляд). Давайте запишем последовательность действий в `resize`, если `new_size > capacity`:

1. Резервируем достаточно новой памяти.
2. Пытаемся сконструировать новые объекты в новой памяти.
3. Если получился пункт 2, то пытаемся перенести старые объекты в новую память.
4. Если получился пункт 3, то удаляем все старые объекты из старого хранилища, удаляем старое хранилище и на его место ставим новое.

Если же какой-то пункт не удался (произошло исключение, например), то говорим: "Дружище, сори, не лезу", удаляем новосозданные объекты (если таковы имеются), подчищаем память, которую выделили в пункте 1 и пробрасываем исключение дальше. В остальном делаем вид, что ничего не произошло.

Почему именно так? Обсудим ниже, а пока скажу, что есть другой вариант, с которым вы можете ознакомиться в [курсе](https://www.coursera.org/learn/c-plus-plus-black#syllabus) "Чёрного пояса" от Яндекса на Курсере. Там сначала выделяется новая память (наш п.1), переносятся старые объекты (наш п.3), удаляется старая память (наш п.4) и происходит попытка сконструировать новые объекты (наш п.2). Иными словами, делается `reserve`, а потом п.2. В итоге мы получаем почти тоже самое. Если наш тип не кидается исключениями при создании, то мы даже почти не заметим разницы между этими двумя реализациями (но она будет в последовательности констуировании объектов), а вот если произойдёт исключение, то гарантированно изменится `capacity`, т.е. памяти под тоже самое количество объектов будет выделено уже в два раза больше и гарантировано произойдёт `size` копирований, хотя содержимое нашего вектора никак не поменялось (кроме `capacity`).

Идея же нашей реализация заключается в том, что мы всегда пытаемся сконструировать / переместить наименьшее кол-во объектов и лишний раз не хотим напороться на неприятности. Мы понимаем, что перенести старые объекта с места на место безопаснее, чем конструировать новые.

---

Об общем поговорили, теперь можем приступить к реализации:

```c++
#include <cstddef>  // for std::size_t
#include <memory>
#include <utility>

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type = std::size_t;

    using reference = value_type&;
    using const_reference = const value_type&;

    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = pointer;
    using const_iterator = const_pointer;
```

Мы уже достаточно взрослые (в рамках C++) ребята и девчата и пишем относительно серьёзные классы, так что давайте использовать некоторые юзинги, которые используются в стандартном векторе (конечно, в оригинале всё несколько сложней). Со всеми оригинальными юзингами можно ознакомиться на [страничке](https://en.cppreference.com/w/cpp/container/vector) вектора на cppreference в разделе **Member types**. Немного странно выглядит юзинг на итератор, но тут я не буду реализовывать отдельный класс для него, ибо задача про другое, но я хочу подчеркнуть, что у методов `begin` и `end` несколько другой смысл, нежели у простого указателя.

---

```c++
private:
    size_type size_{0};
    size_type capacity_{0};
    value_type *data_{nullptr};

    pointer _allocate(size_type capacity) {
        void *new_data = operator new(sizeof(value_type) * capacity);
        return reinterpret_cast<value_type *>(new_data);
    }

    void _deallocate() {
        std::destroy_n(data_, size());
        operator delete(data_);

        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }
```

Как и обещалось, мы создали три поля, которые по умолчанию инициализируем нулями, а более нам и не надо. Теперь отдельно рассмотрим две функции, которые мы написали:

1. `_allocate` возвращает указатель на блок памяти в которое влезет `capacity` объектов типа `value_type`. А так как `new_data` - переменная типа `void *`, там не создаются новые объекты данного типа. Далее мы кастуем `new_data` к типу `pointer` и возвращаем её.

2. `_deallocate` ничего не возвращает, но при этом вызывает магическую функцию `std::destroy_n`. Эта функция появилась в `C++17` в заголовочном файле `<memory>`. Из её названия сразу понятно, что она делает - она ~~удаляет~~ вызывает деструкторы для `n` объектов. А это именно то, что нам и нужно! Запомнили и записали. Далее в `_deallocate` возвращаем всю память системе и зануляем приватные поля.

---

```c++
public:
    Vector() noexcept = default;

    explicit Vector(size_type count)
    : capacity_{count}, data_{_allocate(capacity())} {
        try {
            std::uninitialized_value_construct_n(begin(), capacity());
            size_ = count;
        } catch (...) {
            _deallocate();
            throw;
        }
    }

    Vector(const Vector<T>& other)
    : capacity_{other.size()}, data_{_allocate(capacity())} {
        try {
            std::uninitialized_copy(other.cbegin(), other.cend(), data_);
            size_ = other.size();
        } catch (...) {
            _deallocate();
            throw;
        }
    }
```

Тут мы вплотную подошли к функциям вида `std::uninitialized_*`. Все они объявлены в `<memory>`, с их возможной реализацией вы можете ознакомиться по [ссылке](https://en.cppreference.com/w/cpp/header/memory#Functions) и в целом из названия ясно что делает каждая из них, но давайте скажем пару слов, что делает, например `std::uninitialized_copy`. Функция ждёт три итератора и делает примерно тоже самое, что и стандартный `std::copy`, но слово `uninitialized` подчёркивает, что мы работаем с сырой памятью и действительно, функция реализована так, что каждое создание объекта обёрнуто в `try-catch` блок. И в случае ошибки не случится утечки памяти. Нечто похожее вы могли наблюдать в конструкторе коварной матрицы два контеста назад. Разбор той задачи с комментариями про `try-catch` доступен по [ссылке](https://gist.github.com/alzobnin/e0bbb0e3b5f72a778a115924ec2df3f1).

Ещё пару слов скажу, почему переменная `size_` инициализируется нужным значением только после удачного копирования / создания объектов. Дело в том, что `_deallocate` уничтожает ровно `size_` объектов, а в случае ошибки функция `uninitialized_*` всё подчистит и у нас будет ровно ноль объектов.

---

```c++
    ~Vector() {
        _deallocate();
    }
```

Деструктор крайне прост. `std::destroy_n` удаляет элементы от первого до последнего, что позволяет нам не думать о последовательности отдельно и просто вызывать `_deallocate`.

---

```c++
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        _deallocate();
        data_ = _allocate(other.size());
        try {
            std::uninitialized_copy(other.cbegin(), other.cend(), data_);
            size_ = other.size();
            capacity_ = other.size();
        } catch (...) {
            _deallocate();
            throw;
        }
        return *this;
    }

    void swap(Vector& other) noexcept {
        if (this != &other) {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(data_, other.data_);
        }
    }
```

Оператор присвивания таит в себе ловушку. Хочется сделать `_deallocate`, затем `_allocate`, а потом скопировать всё, что нам надо скопировать, но это может дорого нам стоить, ведь никто не застрахован от конструкций вида `variable = variable`. Конечно, в наше время компиляторы и IDE умеют распознавать и ругаться на такой код, но это останавливает далеко не всех. В связи с этим, если мы не будем делать проверку, что `this == &other`, то можем удалить ту же информацию, что потом собираемся копировать. Так что не забываем про проверку на присваивание самого себя к себе же и делаем уже знакомые нам действия.

Со свапом такая же история. Делать `a.swap(a)` мы не хотим (да и не за чем), так что тоже добавим проверку на равенство ссылок.

---

```c++
    reference operator[](size_type pos) {
        return data()[pos];
    }

    const_reference operator[](size_type pos) const {
        return const_cast<const_reference>(data()[pos]);
    }

    pointer data() noexcept {
        return data_;
    }

    const_pointer data() const noexcept {
        return const_cast<const_pointer>(data_);
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type capacity() const noexcept {
        return capacity_;
    }
```

Вместе с константным и неконстантным оператороми `[]` реализуем метод `data()`, который, как и в стандартном `std::vector` будет нам возвращать константный и неконстантный указатель на наши объекты.

В константных версиях воспользуемся `const_cast` в `const_*`, чтобы подчеркнуть то, что мы возвращаем константные объекты.

Методы `size` и `capacity` особо комментировать не хочется. Весят их копии столько же, сколько и ссылка на них, так что смело возвращаем `size_type` без всяких `const` и `&`.

---

```c++
    iterator begin() noexcept {
        return data();
    }

    const_iterator begin() const noexcept {
        return const_cast<const_iterator>(data());
    }

    const_iterator cbegin() const noexcept {
        return begin();
    }

    iterator end() noexcept {
        return begin() + size();
    }

    const_iterator end() const noexcept {
        return cbegin() + size();
    }

    const_iterator cend() const noexcept {
        return end();
    }
```

Я большой любитель `cbegin` и `cend`, так что реализуем и их тоже, несмотря на то, что речи о них в условии нет. Тут тоже будем использовать каст в `const_iterator` дабы подчеркнуть константность. 

---

```c++
    void reserve(size_type new_cap) {
        if (new_cap <= capacity()) {
            return;
        }
        auto new_data = _allocate(new_cap);
        try {
            std::uninitialized_copy(cbegin(), cend(), new_data);
            std::swap(data_, new_data);
            std::destroy_n(new_data, size());
            operator delete(new_data);
            capacity_ = new_cap;
        } catch (...) {
            operator delete(new_data);
            throw;
        }
    }
```

Мы хотим резервировать память только в большую сторону, так что если нам этого делать не нужно, то не делаем ничего. Далее мы выделяем новую память и пытаемся туда переместить копии имеющихся объектов. Потом удаляем старую память. Если поймали ошибку, то удаляем новую память, а исходный вектор остаётся нетронутым.

---

```c++
    void clear() noexcept {
        std::destroy_n(data(), size());
        size_ = 0;
    }

    void pop_back() {
        std::destroy_at(end() - 1);
        --size_;
    }
```

Функция `clear` линейна по своей сути. Основная идея - мы не трогаем `capacity` и уничтожаем всё от первого к последнему созданному ранее объекту. В реализаци `pop_back` мы используем другую функцию стандартной библиотеки - `std::destroy_at`. Из её названия так же ясно, что она делает. Замечу, что `pop_back` из пустого вектора вызовет неопределённое поведение, но нам и не нужно обрабатывать эту ситуацию.

---

```c++
    void push_back(const_reference value) {
        if (size() == capacity()) {
            const auto new_cap = !capacity() ? static_cast<size_type>(1) : capacity() * 2;
            auto new_data = _allocate(new_cap);

            try {  // trying to create a new object
                new (new_data + size()) value_type(value);
            } catch (...) {
                operator delete(new_data);
                throw;
            }

            try {  // copy old data
                std::uninitialized_copy(cbegin(), cend(), new_data);
                std::swap(data_, new_data);
                std::destroy_n(new_data, size());
                operator delete(new_data);
                capacity_ = new_cap;
                ++size_;
            } catch (...) {
                std::destroy_at(new_data + size());  // delete created object
                operator delete(new_data);
                throw;
            }
        } else {
            new (end()) value_type(value);
            ++size_;
        }
    }
```

Тут у нас есть `if`, который разбивает `push_back` на две части. Во второй части (в `else`) всё ясно, у нас есть место куда можно вставить новый элемент, им мы и пользуемся. Если произошла ошибка при копировании нового объекта, то мы сразу пробросим эту ошибку наружу, а `size` останется неизменным.

В первой части нам нужно сделать реалокацию памяти. Теперь давайте вспомним те 4 пункта, о которых мы говорили в самом начале. Изначально мы определяем сколько памяти нам нужно выделить. Это `push_back`, а значит, выделяем ровно в два раза больше, если не ноль и под один элемент, если ноль. Далее, пытаемся сконструировать новый объект в новой памяти. Если не получилось, то чистим память и, грустно вздыхая, кидаемся ошибкой. Если же всё вышло, то используем уже привычную нам функцию `std::uninitialized_copy` для создания копий старых объектов в новой памяти. Тут главное не забыть вызвать деструктор у новосозданного объекта в случае ошибки. Если всё прошло успешно, меняем `size` и `capacity`. 

---

```c++
    void resize(size_type new_size) {
        if (new_size <= size()) {
            std::destroy_n(begin() + new_size, size() - new_size);
        } else if (new_size <= capacity()) {
            std::uninitialized_value_construct_n(end(), new_size - size());
        } else {
            auto new_data = _allocate(new_size);

            try {
                std::uninitialized_value_construct_n(new_data + size(), new_size - size());
            } catch (...) {
                operator delete(new_data);
                throw;
            }

            try {
                std::uninitialized_copy(cbegin(), cend(), new_data);
                std::swap(data_, new_data);
                std::destroy_n(new_data, size());
                operator delete(new_data);
                capacity_ = new_size;
            } catch (...) {
                std::destroy_n(new_data + size(), new_size - size());
                operator delete(new_data);
                throw;
            }
        }
        size_ = new_size;
    }
};
```

Функция `resize` не сильно отличается от `push_back` идеологически. Только тут у нас `size` кроме роста вверх может убывать или вовсе не поменяться. Это учитывается в первом `if`.

Если же нам не надо делать реаллокацию, а размер увеличивается, то используем уже знакомую из конструктора функцию `uninitialized_value_construct_n`.

В третьем случае мы почти полностью копируем `push_back`. Только учитываем, что создаём не один определённый объект, а несколько дефолтных. При реалокации оригинальный вектор использует нечто вроде `std::move_if_noexcept` при переносе старых объектов в новую память. Но в этой задаче мы не требовали от вас использования подобных функций.

---