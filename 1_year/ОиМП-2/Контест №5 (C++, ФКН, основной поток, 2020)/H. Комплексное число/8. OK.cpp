#include <deque>
#include <iostream>

template<typename T, typename Container = std::deque<T>>
class Queue {
    Container NewQueue;

    // 1. Конструктор по умолчанию, создающий пустую очередь.
    Queue() {
        NewQueue;
    }

    // 2. Константную функцию front, возвращающую элемент, стоящий в начале очереди.
    const T front() const {
        return *NewQueue.front();
    }

    // 3. Неконстантную функцию front, возвращающую по ссылке элемент,
    // стоящий в начале очереди (и тем самым позволяющую его изменять).
    T &front() {
        return NewQueue.front();
    }

    // 4. Функцию pop, убирающую элемент из начала очереди (и ничего не возвращающую).
    void pop() {
        NewQueue.pop_front();
    }

    // 5. Функцию push, кладущую переданный элемент в конец очереди.
    void push(T a) {
        NewQueue.push_back(a);
    }

    // 6. Функцию size, возвращающую количество элементов.
    int size() {
        return NewQueue.size();
    }

    // 7. Функцию empty, возвращающую true тогда и только тогда, когда очередь пуста.
    bool empty() {
        return NewQueue.empty();
    }

    // 8. Операторы == и != для сравнения двух очередей.
    bool operator==(Queue line) {
        if (line.size() != this->size()) {
            return false;
        } else {
            int *it = line.begin();
            for (T &iter : this) {
                if (iter != *it) {
                    return false;
                } else {
                    it++;
                }
            }
        }
    }

    bool operator!=(Queue line) {
        return !(this == line);
    }
};
/*
int main() {
    std::deque<int> T1 = {1, 2, 3, 4};
    std::deque<int> T2 = {2, 3, 4, 1};
    T1.pop_back();
    T1 >= T2 ? std::cout << "YES" : std::cout << "NO";
    return 0;
}
*/