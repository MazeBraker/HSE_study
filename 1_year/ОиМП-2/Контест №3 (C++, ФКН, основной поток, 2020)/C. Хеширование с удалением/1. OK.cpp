#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    set<char> alp;
    string alp1;
    cin >> alp1;
    for (int i = 0; i < alp1.size(); i++) {
        alp.insert(alp1[i]);
    }
    int n, k = 0;
    string slova;
    cin >> n;

    for (int i = 0; i <= n; i++) {
        if (k != 1) {
            cout << slova << endl;
        }
        cin >> slova;
        k = 0;
        for (int j = 0; j < slova.size(); j++) {
            if (alp.find(slova[j]) == alp.end()) {
                k = 1;
                break;
            }
        }
    }
    return 0;
}