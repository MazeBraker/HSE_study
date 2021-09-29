#include <cmath>
#include <iostream>
#include <memory>
#include <string>

template<typename T>
class IntegrationMethod {
    virtual double Integrate(F f, double a, double b, int n) const {}
};

template<typename T>
class RectangleRule : public IntegrationMethod<T> {
    double Integrate(F f, double a, double b, int n) const {
        double area = 0;
        double x_i = 0, x_i1;
        // x_i=a + (b - a)*i/n
        for (int i = 0; i != n; ++i) {
            x_i = a + ((b - a) * i) / n;
            x_i1 = a + ((b - a) * (i + 1) / n);
            area += (f((x_i + x_i1) / 2)) * (x_i1 - x_i);
        }
        return area;
    }
};

template<typename T>
class TrapezoidalRule : public IntegrationMethod<T> {
    double Integrate(F f, double a, double b, int n) const {
        double area = 0;
        double x_i = 0, x_i1;
        for (int i = 0; i != n; ++i) {
            x_i = a + ((b - a) * i) / n;
            x_i1 = a + ((b - a) * (i + 1) / n);
            area += ((f(x_i) + f(x_i1)) / 2) * (x_i1 - x_i);
        }
        return area;
    }
};