#include <iostream>
#include <deque>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

struct Min {
    deque<int> f;

    void push(int n) {
        while (!f.empty() && f.back() > n)
            f.pop_back();
        f.push_back(n);
    }

    int min() const {
        return f.front();
    }

    void pop(int n) {
        if (!f.empty() && f.front() == n)
            f.pop_front();
    }
};

int main() {
    Min m;
    int n, l;
    cin >> n >> l;
    typedef istream_iterator<int> in;
    vector<int> v(n);
    copy(in(cin), in(), v.begin());

    for (int i = 0; i < l; ++i)
        m.push(v[i]);

    cout << m.min() << '\n';
    for (int i = l; i < n; ++i) {
        m.push(v[i]);
        m.pop(v[i - l]);
        cout << m.min() << '\n';
    }

    return 0;
}