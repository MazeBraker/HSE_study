#include "c.h"
#include <utility>

int main() {
    C(c1);
    C(std::move(c1));
}