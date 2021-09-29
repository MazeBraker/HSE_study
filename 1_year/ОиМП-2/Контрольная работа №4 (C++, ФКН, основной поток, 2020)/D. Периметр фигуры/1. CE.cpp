#include <iostream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Figure {
public:
    virtual double Perimeter() const;
};

class Rectangle : Figure {
public:
    Rectangle(double a, double b) : A(a), B(b) {}

    double Perimeter() const override { return 2 * A + 2 * B; }

private:
    double A;
    double B;
};

class Triangle : Figure {
public:
    Triangle(double a, double b, double c) : A(a), B(b), C(c) {}

    double Perimeter() const override { return A + B + C; }

private:
    double A;
    double B;
    double C;
};