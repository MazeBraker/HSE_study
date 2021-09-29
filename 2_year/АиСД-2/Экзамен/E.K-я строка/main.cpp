#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

#define ll long long

using namespace std;

struct Node {
    char x;
    int cnt;
    int end;
    Node *a[26];
    
    Node(char x): x(x) {
        cnt = 0;
        end = 0;
//        memset(a, 0, 26);
        for (int i = 0; i < 26; ++i) {
            a[i] = NULL;
        }
    }
    Node(): x(0) {
        cnt = 0;
        end = 0;
//        memset(a, 0, 26);
        for (int i = 0; i < 26; ++i) {
            a[i] = NULL;
        }
    }
};

void add(Node *t, string &s, int i) {
    t->cnt++;
    if (i == s.size()) {
        t->end++;
        return;    
    }
    char v = s[i] - 'a';
    if (!t->a[v]) {
        t->a[v] = new Node(s[i]);
    }
    add(t->a[v], s, i + 1);
}

void print(Node *t, int k) {
    if (k == 0)
        return;
    for (int i = 0; i < 26; ++i) {
        if (t->a[i]) {
            if (t->a[i]->cnt >= k) {
                cout << char('a' + i);
                print(t->a[i], k - t->a[i]->end);
                return;
            }
            k -= t->a[i]->cnt;
        }
    }
}

/*
6
abc
bbc
aac
1
2
3
*/

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin >> n;
    Node *root = new Node();
    
    while (n--) {
        string s;
        cin >> s;
        if (isdigit(s[0])) {
            print(root, stoi(s));
            cout << '\n';
        } else {
            add(root, s, 0);
        }
    }
}