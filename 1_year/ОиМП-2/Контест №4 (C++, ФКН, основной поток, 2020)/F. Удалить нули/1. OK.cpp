#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
template <typename Iter>
Iter unique(Iter first, Iter last) {
    Iter it = first;
    Iter ans = first;
    while (it + 1 != last) {
        if (*it == *ans) {
            ++it;
        } else {
            ++ans;
            *ans = *it;
        }
    }
    return ans + 1;
}