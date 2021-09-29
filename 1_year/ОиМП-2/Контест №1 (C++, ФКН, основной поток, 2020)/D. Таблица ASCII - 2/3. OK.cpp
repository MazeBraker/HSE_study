#include <iostream>
#include <vector>
#include <algorithm>
/* обратные перестановки
 * Находим индексы снизу и сортируем
*/
using namespace std;

int main() {
    int p;
    cin >> p;
    vector<std::pair<int, int>> arr;
    arr.resize(p);
    for (auto i = 0; i <= p - 1; i++) {
        cin >> arr[i].first;
        arr[i].second = i + 1;
        /*cout << arr[i].second << endl;*/
    }
    sort(arr.begin(), arr.end());
    for (auto i = 0; i <= p - 1; i++) {
        cout << arr[i].second << " ";
    }
    return 0;
}
