// можно было  бы написать стоит ли между закрытой и открытой скобкой
// запятая или нет
#include <iostream>
#include <memory>

int k = 1, t = 1, l = 10, f = 5;

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
        if (f == 1) {
            std::cout << "[";
        } else if (k == 1 && t == 1) {
            std::cout << "[";
        } else {
            std::cout << ',' << '[';
            f = 1;
            l = 1;
        }
    }

    void EndArray() {
        t = 0;
        std::cout << "]";
    }

    void AddArrayItem(const std::string &str) {
        f = 0;
        if (l != 1 && (k == 0 || t == 0)) {
            std::cout << ',' << '"' << str << '"';
        } else {
            k = 0;
            std::cout << '"' << str << '"';
            l = 0;
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