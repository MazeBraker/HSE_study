#include <iostream>

int k = 0;

class Serializer {
public:
    virtual void BeginArray() {}

    virtual void AddArrayItem(const std::string &) {}

    virtual void EndArray() {}

    virtual ~Serializer() {}
};

class JsonSerializer : public Serializer {
public:
    void BeginArray() {
        std::cout << "[";
    }

    void EndArray() {
        std::cout << "]";
    }

    void AddArrayItem(const std::string &str) {
        if (k == 0) {
            std::cout << '"' << str << '"';
            ++k;
        } else if (k != 0) {
            std::cout << "," << '"' << str << '"';
        }
    }
};
/*
int main() {
    std::string task, text;
    while(std::cin >> task) {
        if (task == "AddArrayItem") {
            std::cin >> text;
            std::shared_ptr<JsonSerializer> ptr1(new JsonSerializer);
            ptr1->AddArrayItem(text);
        } else if (task == "BeginArray") {
            std::shared_ptr<JsonSerializer> ptr1(new JsonSerializer);
            ptr1->BeginArray();
        } else if (task == "EndArray") {
            std::shared_ptr<JsonSerializer> ptr1(new JsonSerializer);
            ptr1->EndArray();
        }
    }
}*/