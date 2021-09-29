#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename T>
void Duplicate(std::vector<T> &v) {
    for (auto &it : v) {
        v.push_back(it);
    auto filtered_last = std::copy_if(
            data.begin(),
            data.end(),
            std::back_inserter(filtered),
    }
}
/*
int main(){
    std::vector<int> v = {1,2,3,4,5,6,7};
    Duplicate(v);
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << ",";
    }
    return 0;
}
*/