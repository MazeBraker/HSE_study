#include "writer.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

class BufferedWriter : public Writer {
private:
    char *Null = nullptr;
    size_t bytes = 0, curbyte = 0;

public:
    BufferedWriter(size_t len) {
        bytes = len;
    }

    //  дописывать данные в этот внутренний буфер
   void Write(const char * data, size_t len) override {
        auto info = *data;
        size_t i = 0;
        while (i != len) {
            *Null = *data;
            ++data;
            ++curbyte;
            if (curbyte == bytes) {
                Writer::Write(Null, bytes);
                Null = nullptr;
            }
            i++;
        }
    }

    ~BufferedWriter() {
        Writer::Write(Null, bytes);
    }
};