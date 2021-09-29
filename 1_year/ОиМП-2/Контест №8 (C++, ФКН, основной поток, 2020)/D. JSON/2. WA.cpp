// можно было  бы написать стоит ли между закрытой и открытой скобкой
// запятая или нет
#include <iostream>

int k = 1, t = 1;

class Serializer {
public:
    virtual void BeginArray() = 0;

    virtual void AddArrayItem(const std::string &) = 0;

    virtual void EndArray() = 0;

    virtual ~Serializer() {}
};

class JsonSerializer : public Serializer {
public:
    void BeginArray() {
        if (k == 1 && t == 1) {
            std::cout << "[";
        } else {
            std::cout << ',' << '[';
        }
    }

    void EndArray() {
        t = 0;
        std::cout << "]";
    }

    void AddArrayItem(const std::string &str) {
        if (k == 0 || t == 0) {
            std::cout << ',' << '"' << str << '"';
        } else {
            k = 0;
            std::cout << '"' << str << '"';
        }
    }
};
/*
int main() {
    std::string task, text;
    while (std::cin >> task) {
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