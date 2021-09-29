#include <cstddef>
#include <cstring>

namespace my_cstring {
    size_t strlen(const char *s) {
        const char *end = s;
        while (*end++ != 0) {}
        return end - s - 1;
    }
}