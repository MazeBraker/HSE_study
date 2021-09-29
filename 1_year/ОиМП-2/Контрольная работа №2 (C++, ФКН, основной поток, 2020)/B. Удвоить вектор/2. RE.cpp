#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <ctype.h>


void RemoveDuplicates(std::deque<int>& data) {
    data.erase(std::unique(data.begin(), data.end()), data.end());
}

