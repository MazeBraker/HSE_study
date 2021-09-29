#include "c.h"
#include <utility>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<C *> v;
    for (int i = 0; i < n; i++) {
        C *c = new C;
        v.push_back(c);
    }
    for (int i = 0; i < n; i++) {
        delete v[i];
    }
}