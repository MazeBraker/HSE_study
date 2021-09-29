#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Для простых примитивных типов (int, bool, char и т. д.) и plain old data
template<typename T>
void Serialize(T pod, std::ostream &out) {
    out.write(reinterpret_cast<char *>(&pod), sizeof(pod));
}

template<typename T>
void Deserialize(std::istream &in, T &pod) {
    in.read(reinterpret_cast<char *>(&pod), sizeof(pod));
}

// для строк
void Serialize(const std::string &str, std::ostream &out) {
    size_t size = str.length();
    out.write(reinterpret_cast<char *>(&size), sizeof(size_t));
    out.write(str.c_str(), size);
}

void Deserialize(std::istream &in, std::string &str) {
    size_t size = 0;
    str.resize(size);
    in.read(reinterpret_cast<char *>(str.data()), sizeof(char) * size);
    for (size_t i = 0; i != size; i++) {
        Deserialize(in, str[i]);
    }
}

// для векторов
template<typename T>
void Serialize(const std::vector<T> &data, std::ostream &out) {
    const size_t size = data.size();
    out.write(reinterpret_cast<const char *>(&size), sizeof(size_t));
    for (size_t i = 0; i < data.size(); i++) {
        Serialize(data[i], out);
    }
}

template<typename T>
void Deserialize(std::istream &in, std::vector<T> &data) {
    size_t size = 0;
    in.read(reinterpret_cast<char *>(&size), sizeof(size));
    data.resize(size);
    in.read(reinterpret_cast<char *>(data.data()), sizeof(T) * size);
}

// для словарей
template<typename T1, typename T2>
void Serialize(const std::map<T1, T2> &data, std::ostream &out) {
    const auto size = data.size();
    out.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (const auto item : data) {
        Serialize(item.first, out);
        Serialize(item.second, out);
    }
}

template<typename T1, typename T2>
void Deserialize(std::istream &in, std::map<T1, T2> &data) {
    size_t size = 0;
    in.read(reinterpret_cast<char *>(&size), sizeof(size));
    for (size_t i = 0; i != size; i++) {
        T1 key;
        Deserialize(in, key);
        T2 value;
        Deserialize(in, value);
        data[key] = value;
    }
}