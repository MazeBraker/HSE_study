#include<iostream>
#include<cstring>

using namespace std;

int main() {
    char str1[50000];
    cin >> str1;
    int d1;
    bool f_yes;
    d1 = strlen(str1);
    f_yes = true;

    for (int i = 0; i < d1; i++)
        if (str1[i] != str1[d1 - i - 1])
            f_yes = false;
    if (f_yes)
        cout << "yes";
    else
        cout << "no";

    return 0;
}