#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    int letters = 0, words = 0, lines = 0;
    string s;
    ifstream file;
    file.open("input.txt");
    getline(file, s, '\n');
    file.close();
    for (auto i = 0; i < s.size(); ++i) {
        if (isalpha(s[i]))
            letters++;
        if (isalpha(s[i + 1]) == 0
            && isalpha(s[i]))
            words++;
        if (s[i] == '\n')
            lines++;
    }

    printf("Input file contains:  \n");
    cout << letters << " letters \n"
         << words << " words \n"
         << lines << " lines \n";

    return 0;
}