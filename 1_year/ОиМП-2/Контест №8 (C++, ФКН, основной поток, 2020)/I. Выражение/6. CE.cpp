#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Document {
// Clion говорит protected))
// производные классы получают свободный доступ * Иерархия
protected:
    const std::string Content;
public:
    Document(const std::string &s) : Content(s) {}

    // virtual save * полиформна
    virtual void Save() const {
    }
};

class PlainTextDocument : public Document {
public:
    PlainTextDocument(const std::string &s) : Document(s) {}

    // override
    void Save() const override {
        std::cout << Content << "\n";
    }
};

class HTMLDocument : public Document {
public:
    HTMLDocument(const std::string &s) : Document(s) {}

    // override
    void Save() const override {
        std::cout << "<HTML><BODY>" << Content << "</BODY></HTML>\n";
    }
};
// cнова uniqueptr * DocumentCollection должен быть вектором
using DocumentCollection = std::vector<std::unique_ptr < Document>>;

void AddDocument(const std::string &content, const std::string &type,
                 DocumentCollection &collection) {
    if (type == "plain")
        // так же как и впред задаче создать на стеке, * сигнатуры
        collection.push_back(std::unique_ptr<PlainTextDocument>(new PlainTextDocument(content)));
    else if (type == "html")
        collection.push_back(std::unique_ptr<HTMLDocument>(new HTMLDocument(content)));
}

// умный указатель . -> * Утечки памяти
void PrintCollection(const DocumentCollection &collection) {
    for (const auto &doc : collection)
        doc->Save();
}