#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int N, k;
    std::vector<int> nums;
    std::cin >> N >> k;
    // ввели числа в вектор
    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        nums.push_back(x);
    }
    // отсортировали по возвр
    sort(nums.begin(), nums.end());
    //std::cout << nums[0] << nums[1];

    int sum = nums[0], cnt = 0;
    // впихиваем пока можем
    for (int i = 0; i < k; i++) {
        if (sum <= N) {
            cnt++;
            sum += nums[cnt];
        } else break;
    }

    std::cout << cnt;
    return 0;
}