#include <iostream>
#include <cmath>
//  Семинар
using namespace std;

class Complex {
private:
    double real;
    double im;

public:
    Complex(double real, double im = 0) : real(real), im(im) {}

    friend Complex operator+(Complex a, Complex b);

    friend Complex operator-(Complex a, Complex b);

    friend Complex operator*(Complex a, Complex b);

    friend Complex operator/(Complex a, Complex b);

    friend Complex operator-(Complex a);

    friend Complex operator+(Complex a);

    friend bool operator==(Complex a, Complex b);

    friend bool operator!=(Complex a, Complex b);

    friend double abs(Complex a);

    double Re() const {
        return real;
    }

    double Im() const {
        return im;
    }
};

double abs(Complex a) {
    return sqrt(a.im * a.im + a.real * a.real);
}

Complex operator+(Complex a, Complex b) {
    return Complex(a.real + b.real, a.im + b.im);
}

Complex operator-(Complex a, Complex b) {
    return Complex(a.real - b.real, a.im - b.im);
}

Complex operator*(Complex a, Complex b) {
    return Complex(a.real * b.real - a.im * b.im, a.real * b.im + a.im * b.real);
}

Complex operator/(Complex a, Complex b) {
    return Complex((a.real * b.real + a.im * b.im) / (b.real * b.real + b.im * b.im),

                   (a.im * b.real - a.real * b.im) / (b.real * b.real + b.im * b.im));
}

Complex operator-(Complex a) {
    return Complex(-a.real, -a.im);
}

Complex operator+(Complex a) {
    return Complex(a.real, a.im);
}

bool operator==(Complex a, Complex b) {
    return a.real == b.real && a.im == b.im;
}

bool operator!=(Complex a, Complex b) {
    return !(a.real == b.real && a.im == b.im);
}
/*
int main() {
    Complex a(2, 1);
    Complex b(3, -1);
    Complex c1 = a+b;
    cout << c1.Re() << " " << c1.Im() << '\n';
    Complex c2 = b * a;
    cout << c2.Re() << " " << c2.Im() << '\n';
    Complex c3 = b / a; // 2.(a::operator+)
    cout << c3.Re() << " " << c3.Im() << '\n';
    return 0;
}*/