#include <iostream>    // Семинар

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

    double Re() const {
        return real;
    }

    double Im() const {
        return im;
    }
};

Complex operator+(Complex a, Complex b) {
    return Complex(a.real + b.real, a.im + b.im);
}

Complex operator-(Complex a, Complex b) {
    return Complex(a.real - b.real, a.im - b.im);
}

Complex operator*(Complex a, Complex b) {
    return Complex(a.real * b.real - a.im * b.im, a.im * b.real + a.real * b.im);
}

Complex operator/(Complex a, Complex b) {
    return Complex((a.real * a.im + b.im * b.real) / (a.im * a.im + b.im * b.im),
                   (-a.im * b.real + a.real * b.im) / (a.im * a.im + b.im * b.im));
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