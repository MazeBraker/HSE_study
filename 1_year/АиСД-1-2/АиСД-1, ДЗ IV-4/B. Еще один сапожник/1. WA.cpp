#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

bool comp(std::pair<double, double> &x, std::pair<double, double> &y) {
    return (x.second < y.second);
}

// Аналог задачи про пары
// Создаем начало и конец времени работы
int main() {
    int k;
    std::vector<std::pair<double, double>> time;

    std::cin >> k;

    for (int i = 0; i < k; i++) {
        double start, finish;
        std::cin >> finish;
        start = finish - 1.0;
        time.emplace_back(std::make_pair(start, finish));
    }
//сортируем по началу
    sort(time.begin(), time.end(), comp);
// и так проходимся жадно по всем
    int count = 1;
    int curtime = time[0].second;
    int cur = 0;
    while (cur < k) {
        if (time[cur].first < curtime) {
            cur++;
        } else {
            count++;
            curtime = time[cur].second;
        }
    }
    if (time[k - 1].first < 0) {
        std::cout << 0;
        return 0;
    }
    std::cout << count;

    return 0;
}