#include "c.h"
#include <utility>

int main() {
    C(c1);
    C(c2);
    c1 = c2;
    std::move(c1) = std::move(c2);
}