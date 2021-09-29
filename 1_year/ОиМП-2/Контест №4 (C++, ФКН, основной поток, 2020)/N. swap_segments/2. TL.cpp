#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>

/*
using namespace std;

bool condition(int a) {
    if (a % 2 == 0)
        return false;
    else
        return true;
}

int f(int a) {
    return a*a;
}
*/
template <typename InIter, typename OutIter, typename Predicate, typename Action>
OutIter transform_if(InIter first, InIter last, OutIter out, Predicate condition, Action f) {
    if (first == last) {
        return out;
    }
    while (first != last) {
        if (condition(*first)) {
            *out = f(*first);
            ++out;
        }
        ++first;
    }
    ++out;
    return out;
}

/*
int main() {
    vector<int> v1 = {1,2,3,4,5,6,7,8};
    vector<int> d(8);
    auto s = transform_if(v1.begin(), v1.end(), d.begin(), condition, f);
    for (auto i = d.begin(); i != s; ++i){
        cout << *i << " ";
    }
}*/