#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Реализация с помощью bar и 2х массивов
int nil = -1;

bool bar(int num, std::vector<std::vector<int>> &foo, int length, int lh, int rh) {
    // правый сын, следовательно длина +1
    if (foo[num][3]) {
        length += 1;
    }

    if (foo[num][0] != -1) {
        if (foo[foo[num][0]][3] == 0) {
            if (foo[num][3] != 0) {
            } else {
                return false;
            }
        } else {}
        if (foo[foo[num][0]][2] < foo[num][2]) {
            if (foo[foo[num][0]][2] > lh) {
                if (bar(foo[num][0], foo, length, lh, foo[num][2])) {
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        if (nil != -1) {
            if (nil != length)
                return false;
        } else {
            nil = length;
        }
    }

    if (foo[num][1] == -1) {
        if (nil == -1) {
            nil = length;
        } else {
            if (nil != length)
                return false;
        }
    } else {
        if (foo[foo[num][1]][3] != 0) {
        } else {
            if (foo[num][3] != 0) {
            } else {
                return false;
            }
        }
        if (foo[foo[num][1]][2] > foo[num][2]) {
            if ((foo[foo[num][1]][2]) >= rh) {
                return false;
            }
            return bar(foo[num][1], foo, length, foo[num][2], rh);
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    unsigned int tree_size, root_n;
    int mn, mx, len = 100;

    std::cin >> tree_size;

    if (tree_size == 0) {
        std::cout << "YES";
        return 0;
    }

    std::cin >> root_n;

    std::vector<std::vector<int>> foo(tree_size + 1, std::vector<int>(4));
    int i = 1;
    while (i <= tree_size) {
        int number, key, left_son, right_son;
        std::string left, right, color;

        std::cin >> number >> key >> left >> right >> color;
        // Идем с корня


        mn = std::min(key, mn);
        mx = std::max(key, mx);

        left_son = left == "null" ? -1 : stoi(left);

        right_son = right == "null" ? -1 : stoi(right);

        foo[number][0] = left_son;
        foo[number][1] = right_son;
        foo[number][2] = key;

        if (color == "R") {
            foo[number][3] = 0;
        } else if (color == "B") {
            foo[number][3] = 1;
        }
        i++;
    }
    if (foo[root_n][3]) {
        if (bar(root_n, foo, 1, mn - 1, mx + 1)) {
            std::cout << "YES";
            return 0;
        } else {
            std::cout << "NO";
            return 0;
        }
    } else {
        std::cout << "NO";
        return 0;
    }
}