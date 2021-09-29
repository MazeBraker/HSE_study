#include <optional>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>
#include <stdexcept>

template<typename Key1, typename Key2, typename Value>
class BiMap {
private:
    // подсказка с лекции/семинара
    std::unordered_map<Key1, std::shared_ptr<Value>> vault_t1;
    std::unordered_map<Key2, std::shared_ptr<Value>> vault_t2;

public:
    void Insert(const std::optional<Key1> &key1,
                const std::optional<Key2> &key2, const Value &value) {
        bool key1_in = false, key2_in = false;

        if (!key1.has_value() && !key2.has_value()) {
            throw std::invalid_argument("some text");
        }

        if (key1.has_value()) {
            if (vault_t1.find(key1.value()) != vault_t1.end()) {
                key1_in = true;
            }
        }

        if (key2.has_value()) {
            if (vault_t2.find(key2.value()) != vault_t2.end()) {
                key2_in = true;
            }
        }

        if (key1_in || key2_in) {
            throw std::invalid_argument("some text");
        }

        if (key1.has_value()) {
            vault_t1[key1.value()] = std::make_shared<Value>(value);
            if (key2.has_value()) {
                vault_t2[key2.value()] = vault_t1[key1.value()];
            }
        } else if (key2.has_value()) {
            vault_t2[key2.value()] = std::make_shared<Value>(value);
            if (key1.has_value()) {
                vault_t1[key1.value()] = vault_t2[key2.value()];
            }
        }
    }

    Value &GetByPrimaryKey(const Key1 &key) {
        if (!(vault_t1.find(key) == vault_t1.end())) {
            return *vault_t1[key];
        } else {
            throw std::out_of_range("some text");
        }
    }

    const Value &GetByPrimaryKey(const Key1 &key) const {
        if (!(vault_t1.find(key) == vault_t1.end())) {
            return *vault_t1[key];
        } else {
            throw std::out_of_range("some text");
        }
    }

    Value &GetBySecondaryKey(const Key2 &key) {
        size_t z;
        if (!(vault_t2.find(key) == vault_t2.end())) {
            return *vault_t2[key];
        } else {
            throw std::out_of_range("some text");
        }
    }

    const Value &GetBySecondaryKey(const Key2 &key) const {
        if (!(vault_t2.find(key) == vault_t2.end())) {
            return *vault_t2[key];
        } else {
            throw std::out_of_range("some text");
        }
    }
};
/*
#include <iostream>
#include <string>

using namespace std;

struct Student {
    string Surname, Name;
};

ostream &operator<<(ostream &out, const Student &s) {
    return out << s.Surname << " " << s.Name;
}

int main() {
    BiMap<int, string, Student> bimap;  // студента можно определить либо по номеру, либо по логину
    bimap.Insert(42, {}, {"Ivanov", "Ivan"});
    bimap.Insert({}, "cshse-ami-512", {"Petrov", "Petr"});
    bimap.Insert(13, "cshse-ami-999", {"Fedorov", "Fedor"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan

    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    bimap.GetByPrimaryKey(
            13).Name = "Oleg";  // меняем значение по первичному ключу - по вторичному оно тоже должно измениться
    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg
    return 0;
}
*/