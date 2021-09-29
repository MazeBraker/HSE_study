#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Реализация с помощью DFS и 2х массивов

bool DFS(int numb, const std::vector<std::vector<int>> &foo, int length, int lh, int rh) {
    // правый сын, следовательно длина +1
    if (foo[numb][3]) {
        length += 1;
    }

    int nil = -1;

    if (foo[numb][0] != -1) {
        if (foo[foo[numb][0]][3] != 0) {
        } else {
            if (foo[numb][3] != 0) {
            } else {
                return false;
            }
        }
        if (foo[foo[numb][0]][2] < foo[numb][2]) {
            if (foo[foo[numb][0]][2] > lh) {
                if (DFS(foo[numb][0], foo, length, lh, foo[numb][2])) {
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
        if (nil == -1) {
            nil = length;
        } else {
            if (nil != length) {
                return false;
            }
        }
    }

    if (foo[numb][1] == -1) {
        if (nil != -1) return true;
        nil = length;
    } else {
        if (foo[foo[numb][1]][3] == 0) {
            if (foo[numb][3] != 0) {
            } else {
                return false;
            }
        } else {}
        if (foo[foo[numb][1]][2] >= foo[numb][2]) {
            if ((foo[foo[numb][1]][2]) >= rh) {
                return false;
            }
            if ((DFS(foo[numb][1], foo, length, foo[numb][2], rh))) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    unsigned int tree_size, root_n;

    std::cin >> tree_size;

    if (tree_size == 0) {
        std::cout << "YES";
        return 0;
    }

    std::cin >> root_n;

    std::vector<std::vector<int>> foo(tree_size + 1, std::vector<int>(4));

    for (int i = 1; i <= tree_size; ++i) {
        int number, key, left_son, right_son;
        std::string left, right, color;

        std::cin >> number >> key >> left >> right >> color;
        // Идем с корня

        left_son = left == "null" ? -1 : stoi(left);

        right_son = right == "null" ? -1 : stoi(right);

        foo[number][0], foo[number][1], foo[number][2] = left_son, right_son, key;

        int mn = 0, mx;
        if (color == "B") {
            foo[number][3] = 1;
        } else if (color == "R") {
            foo[number][3] = 0;
        }
        mn = std::min(key, mn);
        mx = std::max(key, mx);
        std::cout << (foo[root_n][3] ? DFS(root_n, foo, 1, mn - 1, mx + 1) ? "YES" : "NO" : "NO");
        return 0;
    }
}