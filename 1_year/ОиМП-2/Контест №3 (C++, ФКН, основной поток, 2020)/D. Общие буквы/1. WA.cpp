#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

typedef multiset<char> MySet;
typedef vector<MySet> SetVect;

// Добавили строку
MySet inputSet() {
    string inputString;
    getline(cin, inputString);
    MySet mySet;
// Разбили строку на буквы
    char ch;
    stringstream ss(inputString);
    if (inputString.empty())
        return mySet;
    while (ss >> ch)
        mySet.insert(ch);
    return mySet;
}
// Добавили буквы в вектор
SetVect setToVect() {
    SetVect setVect;
    MySet mySet;
    mySet = inputSet();
    while (!mySet.empty()) {
        setVect.push_back(mySet);
        mySet = inputSet();
    }
    return setVect;
}
// Ищем общие буквы
MySet findCommon(const SetVect &setVect) {
    MySet s, buffer;
    if (setVect.size() == 1) {
        s.clear();
        return s;
    }
    set_intersection(setVect[0].begin(), setVect[0].end(),
                     setVect[1].begin(), setVect[1].end(),
                     inserter(s, s.begin()));
    if (setVect.size() == 2)
        return s;
    for (int i = 2; i < setVect.size(); ++i) {
        buffer.clear();
        set_intersection(s.begin(), s.end(),
                         setVect[i].begin(), setVect[i].end(),
                         inserter(buffer, buffer.begin()));
        swap(s, buffer);
    }
    return s;
}

void setToPrint(const MySet &mySet) {
    for (const char &elem: mySet)
        cout << elem;
}

int main() {
    SetVect vectSet = setToVect();
    MySet mySet = findCommon(vectSet);
    setToPrint(mySet);
    return 0;
}