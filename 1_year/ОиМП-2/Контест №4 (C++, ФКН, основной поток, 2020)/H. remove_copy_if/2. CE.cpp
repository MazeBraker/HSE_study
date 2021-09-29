#include <iostream>
#include <vector>
#include <algorithm>

template <typename It, typename OutputIt>
OutputIt sideways_merge(It first1, It last1, It first2, It last2, OutputIt out) {
    --last2;
    --first2;
    while (first1 != last1 || last2 != first2) {
        if (first1 == last1) {
            *out++ = *last2--;
        } else if (last2 == first2) {
            *out++ = *first1++;
        } else {
            if (*first1 < *last2) {
                *out++ = *first1++;
            } else {
                *out++ = *last2--;
            }
        }
    }
    return out;
}
/*
int main()
{
    std::vector<int> X = {1, 2, 3, 7, 9};
    std::vector<int> Y = {8, 7, 6, 5, 4};
    std::vector<int> Z;
    ::sideways_merge(X.begin(), X.end(), Y.begin(), Y.end(), std::back_inserter(Z));
    for (auto e: Z)
        std::cout << e << ' ';
}
*/