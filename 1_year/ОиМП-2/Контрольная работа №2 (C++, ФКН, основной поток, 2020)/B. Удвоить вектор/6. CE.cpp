#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
template <typename T>
void Duplicate(std::vector<T>& v) {
    for (int &it : v) {
        v.push_back(it);
    }
}
