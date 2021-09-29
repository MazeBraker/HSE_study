#include "writer.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

class BufferedWriter : public Writer {
private:
    char *Data = nullptr;
    size_t bytes = 0;
    size_t size_now = size_t();

public:
    BufferedWriter(size_t len) {
        bytes = len;
    }

    void Write(const char *data, size_t len) override {
        auto info = *data;
        size_t i = 0;
        while (i != len) {
            Data[size_now] = *(data + i);
            size_now += 1;
            if (size_now == bytes) {
                Writer::Write(Data, bytes);
                size_now = 0;
            }
            ++i;
        }
    }

    ~BufferedWriter() {
        Writer::Write(Data, size_now);
        delete[] Data;
    }
};