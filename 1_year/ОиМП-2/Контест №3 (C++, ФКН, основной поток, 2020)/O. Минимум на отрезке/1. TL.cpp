#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    set<string> list;
    string s;
    string sign;
    while (true) {
        getline(cin, s);
        sign = s.substr(0, 1);
        if (sign == "#") {
            break;
        }
        s = s.substr(2, 12);
        if (sign == "+" && list.find(s) == list.end()) {
            list.insert(s);
        } else if (sign == "-" && list.find(s) != list.end()) {
            list.erase(s);
        } else if (sign == "?") {
            if (list.find(s) == list.end()) {
                cout << "NO" << "\n";
            } else {
                cout << "YES" << "\n";
            }
        }
    }
    return 0;
}