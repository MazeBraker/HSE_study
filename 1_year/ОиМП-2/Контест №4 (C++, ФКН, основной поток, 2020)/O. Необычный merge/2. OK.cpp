#include <algorithm>

template <class It1, class It2>
It2 swap_segments(It1 first1, It1 last1, It2 first2) {
    while (first1 != last1) {
        std::swap(first1, first2);
        first1++;
        first2++;
    }
    return first2;
}