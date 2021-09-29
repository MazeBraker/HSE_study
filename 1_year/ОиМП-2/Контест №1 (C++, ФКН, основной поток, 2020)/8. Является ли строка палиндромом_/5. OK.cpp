#include<iostream>
#include<string>


int main() {
    char str1[50000];
    std::cin >> str1;
    int i;
    int d1;
    bool f_yes;
    d1 = strlen(str1);
    f_yes = true;

    for (i = 0; i < d1; i++)
        if (str1[i] != str1[d1 - i - 1])
            f_yes = false;
    if (f_yes)
        std::cout << "yes";
    else
        std::cout << "no";

    return 0;
}