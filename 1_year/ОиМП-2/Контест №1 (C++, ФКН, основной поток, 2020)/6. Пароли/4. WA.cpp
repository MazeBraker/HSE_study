#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

int main() {
    string x;
    size_t letters = 0;
    int words = 0;
    int lines = 0;
    while (getline(cin, x)) {
        if (x == "q")
            break;
        bool f = true;
        for (auto i : x) {
            if ((i == ' ' || i == '\n' || i == '.' || i == ',') ||
                (i == '\'' || i == '"' || i == '-')) {
                f = true;
            } else {
                switch (i) {
                    case ':':
                        break;
                    case '%':
                        break;
                    default:
                        if (i < '0' || i > '9') {
                            letters += 1;
                            if (f)
                                words++;
                            f = false;
                        }
                        break;
                }
            }
        }
//        cout << words << '\n';
        lines++;
    }
    cout << "Input file contains:\n";
    cout << letters << " letters" << '\n';
    cout << words << " words" << '\n';
    cout << lines << " lines" << '\n';
    return 0;
}