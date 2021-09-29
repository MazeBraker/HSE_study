## Разбор задачи «Выражение»

### Условие
Представим арифметическое выражение, содержащее числовые константы и операции сложения и умножения, в виде дерева.
В листьях этого дерева будут находиться константы, а в промежуточных узлах — операции.
Вам дан абстрактный базовый класс `Expression`, представляющий из себя такое дерево:
```cpp
#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
    virtual int Evaluate() const = 0;
    virtual std::string ToString() const = 0;
    virtual ~Expression() {}
};

using ExpressionPtr = std::shared_ptr<Expression>;

#include "your_code.h"

int main() {
    ExpressionPtr ex1 = Sum(Product(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
}
```
Вам надо унаследовать от него классы-наследники для констант, операции сложения и операции умножения так, чтобы приведённый в функции `main` код (и аналогичные примеры) заработали.

Функции базового класса `Evaluate` и `ToString` должны переопределяться в классах-наследниках.
`Evaluate` должна вычислять выражение, а `ToString` возвращать его текстовую запись (как в примере).
При умножении на сумму запись суммы должна браться в скобки.
Никаких особых специальных правил оформления нулевых или единичных множителей писать не нужно.

Кроме классов-наследников, Вам надо будет определить функции `Const`, `Sum` и `Product`, которые используются в функции `main` в примере.
Лишних копирований дерева быть не должно: мы будем проверять, что создано ровно столько экземпляров классов, сколько требуется для построения дерева.
Разумеется, утечек памяти тоже не должно быть.

Для преобразования чисел в строки используете функцию `std::to_string`.


### Решение
```cpp
class ConstExpr: public Expression {
private:
    int value;

public:
    ConstExpr(int v): value(v) {}

    int Evaluate() const override {
        return value;
    }
    std::string ToString() const override {
        return std::to_string(value);
    }
};

class BinaryOperation: public Expression {
protected:
    ExpressionPtr left;
    ExpressionPtr right;

public:
    BinaryOperation(ExpressionPtr l, ExpressionPtr r): left(l), right(r) {}
};

class SumExpr: public BinaryOperation {
public:
    SumExpr(ExpressionPtr l, ExpressionPtr r): BinaryOperation(l, r) {}

    int Evaluate() const override {
        return left->Evaluate() + right->Evaluate();
    }
    std::string ToString() const override {
        return left->ToString() + " + " + right->ToString();
    }
};

class ProductExpr: public BinaryOperation {
private:
    static std::string Parentheses(ExpressionPtr ex) {
        if (dynamic_cast<SumExpr*>(ex.get()))
            return std::string("(") + ex->ToString() + ")";
        else
            return ex->ToString();
    }
public:
    ProductExpr(ExpressionPtr l, ExpressionPtr r): BinaryOperation(l, r) {}

    int Evaluate() const override {
        return left->Evaluate() * right->Evaluate();
    }
    std::string ToString() const override {
        return Parentheses(left) + " * " + Parentheses(right);
    }
};

ExpressionPtr Const(int x) {
    return ExpressionPtr(new ConstExpr(x));
}

ExpressionPtr Sum(ExpressionPtr l, ExpressionPtr r) {
    return ExpressionPtr(new SumExpr(l, r));
}

ExpressionPtr Product(ExpressionPtr l, ExpressionPtr r) {
    return ExpressionPtr(new ProductExpr(l, r));
}
```
Главная сложность здесь — понять, когда надо ставить скобки вокруг суммы в произведении.
Для этого надо понять, является ли подвыражение именно суммой.
К сожалению, базовый класс `Expression` нам недоступен для изменений (иначе можно было бы внести в него виртуальную функцию `NeedParantheses`).
Поэтому можно воспользоваться конструкцией [`dynamic_cast`](https://en.cppreference.com/w/cpp/language/dynamic_cast),
которая в runtime пытается привести указатель на базовый класс к указателю на производный тип
(и возвращает `nullptr`, если это невозможно).
Эта конструкция работает только для иерархий с виртуальными функциями в базовом классе.
В нашем примере она используется в функции `ProductExpr::Parentheses`.