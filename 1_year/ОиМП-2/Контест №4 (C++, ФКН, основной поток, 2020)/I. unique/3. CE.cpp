#include <iostream>
#include <vector>
#include <algorithm>

template<typename InIter, typename OutIter, typename Predicate>
OutIter remove_copy_if(InIter first, InIter last, OutIter out, Predicate f) {
    while (first != last) {
        if (!pred(*first)) {
            *out = *first;
            ++out;
        }
        ++first;
    }
    return out;
}