#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct TPoint {
    int x, y;

    bool operator<(const TPoint &t) const {
        return pow(x, 2) + pow(y, 2) < t.x * t.x + t.y * t.y;
    }
};

ostream &operator<<(ostream &stream, TPoint &Point) {
    return stream << Point.x << " " << Point.y << endl;
}

istream &operator>>(istream &stream, TPoint &Point) {
    return stream >> Point.x >> Point.y;
}

int main() {
    int quant;
    cin >> quant;
    vector<TPoint> Points(quant);
    for (auto &i : Points) {
        cin >> i;
    }
    sort(Points.begin(), Points.end());
    for (auto &i : Points) {
        cout << i;
    }
}