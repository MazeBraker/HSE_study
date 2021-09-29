#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

template<class Iter>
Iter unique(Iter &first, Iter &last) {
    if (first == last)
        return last;

    Iter result = first;
    while (++first != last) {
        if (!(*result == *first)) {
            *(++result) = *first;
        }
    }
    return ++result;
}