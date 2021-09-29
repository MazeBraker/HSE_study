#include "writer.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

class BufferedWriter : public Writer {
private:
    size_t bytes = 0;
    size_t curbyte = 0;
    char *Null = nullptr;

public:
    BufferedWriter(size_t bit) {
        bytes = bit;
    }

    //  дописывать данные в этот внутренний буфер
    void Write(const char *data, size_t bit) override {
        auto info = *data;
        size_t i = 0;
        while (i != bit) {
            *Null = *data;
            ++data;
            ++curbyte;
            if (curbyte == bytes) {
                Null = nullptr;
                Writer::Write(Null, bytes);
            }
            i++;
        }
    }

    ~BufferedWriter() {
        Writer::Write(Null, bytes);
    }
};