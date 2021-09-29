#include <iostream>
#include <string>
#include <locale>

using namespace std;

template<class OutputIterator>
inline OutputIterator convert(const unsigned char *start, const unsigned char *end,
                              OutputIterator out) {
    while (start != end) {
        if (*start < 192) {
            *out++ = *start++;   // single byte character
        } else if (*start >= 224 || start + 1 >= end || *(start + 1) <= 127) {
            if (*start < 240 && start + 2 < end && *(start + 1) > 127 && *(start + 2) > 127) {
                // 3 byte character
                *out++ = ((*start & 0x0F) << 12) | ((*(start + 1) & 0x3F) << 6) |
                         (*(start + 2) & 0x3F);
                start += 3;
            } else if (*start < 248 && start + 3 < end && *(start + 1) > 127 &&
                       *(start + 2) > 127 &&
                       *(start + 3) > 127) {
                // 4-byte character
                *out++ = ((*start & 0x07) << 18) | ((*(start + 1) & 0x3F) << 12) |
                         ((*(start + 2) & 0x3F) << 6) | (*(start + 3) & 0x3F);
                start += 4;
            } else {
                ++start;
            }
        } else {
            // 2 byte character
            *out++ = ((*start & 0x1F) << 6) | (*(start + 1) & 0x3F);
            start += 2;
        }
    }

    return out;
}

int main() {
    std::string s = "\u00EA";
    std::getline(std::cin, s);
    std::wstring output;
    convert(reinterpret_cast<const unsigned char *> (s.c_str()),
            reinterpret_cast<const unsigned char *>(s.c_str()) + s.length(),
            std::back_inserter(output));

    cout << output.length() << "\n";
}