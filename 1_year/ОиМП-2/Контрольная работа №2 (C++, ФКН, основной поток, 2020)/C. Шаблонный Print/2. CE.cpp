#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ostream>

template<typename T>
void Print(const std::vector<T> &v, const char *const separator = ",") {
    if (!v.empty()) {
        std::copy(v.begin(),
                  --v.end(),
                  std::ostream_iterator<T>(std::cout, separator));
        std::cout << v.back() << "\n";
    }
}