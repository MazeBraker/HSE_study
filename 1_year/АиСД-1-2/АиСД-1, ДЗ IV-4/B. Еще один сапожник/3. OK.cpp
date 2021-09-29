#include <iostream>
#include<algorithm>
#include<vector>
#include<utility>

bool foo(std::pair<long long int, long long int> &a, std::pair<long long int, long long int> &b) {
    return ((long long int) ((long long int) a.first / (long long int) a.second) > (long long int)
            ((long long int) b.first / (long long int) b.second));
}

int main() {
    long long int N, weight;
    long long int nowweight = 0;
    double ans = 0.000000;

    std::cin >> N >> weight;

    std::vector<std::pair<long long int, long long int> > silver(N);
    for (long long int i = 0; i < N; i++) {
        std::cin >> silver[i].first >> silver[i].second;
    }

    sort(silver.begin(), silver.end(), foo);


    for (long long int i = 0; i < N && nowweight < weight; i++) {
        if (nowweight + silver[i].second <= weight) {
            ans = ans + silver[i].first;
            nowweight = nowweight + silver[i].second;
        } else {
            ans = ans + (silver[i].first / silver[i].second) * (weight - nowweight);
            nowweight = nowweight + silver[i].second;
        }

    }
    std::cout << std::fixed << ans;
    return 0;
}