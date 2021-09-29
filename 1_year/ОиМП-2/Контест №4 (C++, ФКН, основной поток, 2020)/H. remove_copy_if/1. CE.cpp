#include <iostream>

using namespace std;

template <typename It, typename Pred>
bool any_of(It first, It last, Pred f) {
    while (first != last) {
        if (f(*first))
            return true;
        ++first;
    }
    return false;
}