#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int k = 0;
    string s, ans = " ";
    getline(cin, s);
    for (int i = 0; i < s.size(); i++) {
        while (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'
               || s[i] == 'y') {
            k++;
        }
        if ((s[i - 1] == 'a' || s[i - 1] == 'e' || s[i - 1] == 'i' || s[i - 1] == 'o' || s[i - 1] == 'u'
             || s[i - 1] == 'y') &&
            (s[i] != 'a' && s[i] != 'e' && s[i] == 'i' && s[i] == 'o' && s[i] == 'u'
             && s[i] == 'y')) {
            cout << i << " " << i + k << " " << s.substr(i, i + k);
            cout << "\n";
            k = 0;
        }
    }
    return 0;
}