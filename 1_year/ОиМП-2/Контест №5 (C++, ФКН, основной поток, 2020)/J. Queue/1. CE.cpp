// VIM семинар
#include <iostream>
#include <string>
#include <algorithm>

class Vim {
private:
    int ind, rh;
    std::string text;
    char mode_work;

public:
    Vim(std::string a) {
        text = a;
        ind = 0;
        rh = 0;
        mode_work = 'e';
    }

    void left() {
        ind = std::max(0, --ind);
    }

    void right() {
        ind = std::min(rh, ++ind);
    }

    void chmod(char a) {
        mode_work = a;
    }

    std::string do_it() {
        std::string ans;
        for (int i = 0; i < text.size(); ++i) {
            if (text[i] == '<') {
                i += 4;
                chmod('e');
                continue;
            }
            if (mode_work == 'e' && text[i] == 'i') {
                chmod('i');
                continue;
            }
            if (mode_work == 'e' && text[i] == 'h') {
                left();
                continue;
            }
            if (mode_work == 'e' && text[i] == 'l') {
                right();
                continue;
            }
            if (mode_work == 'i') {
                ans.insert(ans.begin() + ind, text[i]);
                rh++;
                ind++;
            }
        }
        return ans;
    }
};

int main() {
    std::string s;
    std::cin >> s;
    Vim ans(s);
    std::cout << ans.do_it();
}