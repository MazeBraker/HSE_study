// Сделано на семинаре
#include <optional>
#include "classifiers.h"

using std::string;

class CombinedClassifier {
private:
    string simple;
    FastClassifier a;
    std::optional<MainClassifier> b;

public:
    CombinedClassifier(const string &s, const string &c):
    simple(c)
    , a(FastClassifier(s)) {}

    double classify(const string& f) {
        try {
            return a.classify(f);
        } catch(TooHardObjectException) {
            if (!b) {
                b.emplace(simple);
            }
            return b->classify(f);
        }
    }
};