#include "c.h"
#include <utility>
#include <vector>

int main() {
    C *c1 = new C;
    C *c2 = new C;
    C *c3 = new C;
    delete c2;
    delete c3;
    delete c1;
}