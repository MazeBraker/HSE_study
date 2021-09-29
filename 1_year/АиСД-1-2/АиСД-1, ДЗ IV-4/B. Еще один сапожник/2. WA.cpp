#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    int k, count = 0;
    std::cin >> k;
    std::vector<double> arr(k);
    for (double &time : arr) {
        std::cin >> time;
    }
    // сортируем по началу
    sort(arr.begin(), arr.end());
    // жадно берем
    // следим чтобы между работами был 1 час
    for (double &i :arr) {
        if (i - count >= 1) {
            ++count;
        }
    }
    std::cout << count;
}