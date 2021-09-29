#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <ctype.h>
template<typename T>
void removeDuplicates(std::vector<T>& data)
{
    data.erase(std::unique(data.begin(), data.end()), data.end());
}
