#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T>
void process(const std::vector<T>& data) {
    std::vector<T> filtered;
    auto filtered_last = std::copy_if(
            data.begin(),
            data.end(),
            std::back_inserter(filtered),
            [](const T& x) { return x > 0; } );
    print_results(filtered.begin(), filtered.end());
}