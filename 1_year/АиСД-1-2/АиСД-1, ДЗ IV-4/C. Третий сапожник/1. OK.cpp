#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

bool comp(std::pair<double, double> &x, std::pair<double, double> &y) {
    return (x.first > y.first);
}

int k, temp = 0;
double price = 0;

int main() {
    std::cin >> k;
    std::vector<std::pair<double, double>> items(k);

    for (int i = 0; i < k; ++i) {
        std::cin >> items[i].second;
        // выбираем куш, арррр...
        temp = std::max(temp, int(items[i].second));
    }
    for (int i = 0; i < k; ++i) {
        std::cin >> items[i].first;
    }
    std::vector<bool> time(temp);

    std::sort(items.begin(), items.end(), comp);

    for (std::pair<double, double> coins : items) {
        auto i = int(coins.second);
       // std::cout << i << " ";
       i--;
        while (i >= 0) {
            if (time[i]) {
                i--;
                continue;
            }
            time[i] = true;
            price += coins.first;
            break;
        }
    }
    std::cout << price;
	return 0;
}