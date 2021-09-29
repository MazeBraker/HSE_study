## Разбор задачи «Периметр фигуры»

### Условие
Вам надо написать базовый класс `Figure` (геометрическая фигура) и унаследованные от него классы `Triangle` (треугольник) и `Rectangle` (прямоугольник).
Класс `Triangle` должен иметь конструктор, принимающий на вход три числа типа `double` — стороны треугольника.
Считайте, что треугольник с такими сторонами всегда существует.
Класс `Rectangle` должен иметь конструктор, принимающий на вход два числа типа `double` — стороны прямоугольника.
Класс `Figure` должен объвлять виртуальную функцию `double Perimeter() const`, возвращающую периметр фигуры.
Классы-наследники должны переопределить эту функцию правильным образом.

Функцию `main` писать в вашем коде не надо: она будет в нашей проверяющей программе. Наша программа выглядит так:
```cpp
#include "figures.h"

#include <vector>
#include <iostream>

int main() {
    std::vector<Figure*> figures;

    std::string type;
    double val;

    while (std::cin >> type) {
        if (type == "Triangle") {
            int a, b, c;
            std::cin >> a >> b >> c;
            figures.push_back(new Triangle(a, b, c));
        } else if (type == "Rectangle") {
            int a, b;
            std::cin >> a >> b;
            figures.push_back(new Rectangle(a, b));
        }
    }

    for (Figure * f : figures)
        std::cout << f->Perimeter() << "\n";

    for (Figure * f : figures)
        delete f;
}
```

### Решение
Видно, что работа с объектами будет производиться полиморфно,
через указатель на базовый класс `Figure`.
В частности, фигуры будут удаляться через вызов `delete f`, где `f` имеет тип `Figure*`.
Чтобы это корректно работало, в базовом классе нужно предусмотреть виртуальный деструктор.

```cpp
class Figure {
public:
    virtual int Perimeter() const = 0;

    virtual ~Figure() {
    }
};


class Triangle: public Figure {
    int A, B, C;

public:
    Triangle(int x, int y, int z): A(x), B(y), C(z) {
    }

    int Perimeter() const override {
        return A + B + C;
    }
};


class Rectangle: public Figure {
    int A, B;

public:
    Rectangle(int a, int b): A(a), B(b) {
    }

    int Perimeter() const override {
        return 2 * (A + B);
    }
};
```