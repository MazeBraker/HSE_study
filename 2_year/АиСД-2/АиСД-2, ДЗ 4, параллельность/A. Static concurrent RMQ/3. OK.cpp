//Static concurrent RMQ
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <mutex>
#include <future>
#include <execution>

long long INF = 2e10;
int N;
std::vector<long long> tree;

struct Request {
    int left;
    int right;
};

inline long long leftchild(long long n) {
    return n * 2 + 1;
}

inline long long rightchild(long long n) {
    return n * 2 + 2;
}
// из стандартного RMQ
long long get_min(std::vector<long long> &tree, long long v,
                  long long left, long long right, long long l, long long r) {
    if (r <= left || right <= l) {
        return INF;
    }
    if (left <= l && r <= right) {
        return tree[v];
    }
    long long mid = (l + r) / 2;
    return std::min(get_min(tree, leftchild(v), left, right, l, mid),
                    get_min(tree, rightchild(v), left, right, mid, r));
}

// из условия
std::vector<int> ProcessRequests(const std::vector<int> &numbers, const std::vector<Request> &requests) {
    N = numbers.size();
    // высота дерева
    long long tree_h = int(std::ceil(log2(N)));
    // 2 в степени высоты или кол/во листьев
    N = (1 << tree_h);
    tree.assign(2 * N, 0);
    for (int v = N - 1; v <= N - 1 + numbers.size() - 1; ++v) {
        tree[v] = numbers[v - N + 1];
    }
    for (int v = N - 2; v >= 0; --v) {
        tree[v] = std::min(tree[leftchild(v)], tree[rightchild(v)]);
    }

    long long req_num = requests.size();
    std::vector<int> ans(req_num);
    // лямбда фун-ция для get_min
    //Applies an operation sequentially to the elements of one (1)
    //or two (2) ranges and stores the result in the range that begins at result.
    // параллельность по лекции
    std::transform(std::execution::par, requests.begin(), requests.end(), ans.begin(), [](Request req) {
        return get_min(tree, 0, req.left, req.right, 0, N);
    });
    return ans;
}
/*
 * #include "solution.h"

#include <vector>

using namespace std;

int main() {
    const vector<int> numbers = {3, 1, 0, 4};
    const vector<Request> requests = {
        {0, 4},
        {0, 2},
        {1, 3},
        {3, 4}
    };
    for (int result : ProcessRequests(numbers, requests)) {
        cout << result << " ";
    }
    cout << endl;
    // ожидаемый вывод: 0 1 0 4
}
 */