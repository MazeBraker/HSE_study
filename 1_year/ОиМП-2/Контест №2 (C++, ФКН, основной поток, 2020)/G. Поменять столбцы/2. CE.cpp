#include <string>

using namespace std;

string ExtractDigits(const string &s) {
    string ans;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i]))  //проверяет цифры
            ans += s[i];
    }
    return ans;
}