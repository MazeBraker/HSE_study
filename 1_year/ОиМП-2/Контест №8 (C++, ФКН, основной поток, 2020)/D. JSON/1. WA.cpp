#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
    virtual int Evaluate() const = 0;

    virtual std::string ToString() const = 0;

    virtual ~Expression() {}

    int prt;
};

using ExpressionPtr = std::shared_ptr<Expression>;

// #include "your_code.h"

// наследование const
class Const : public Expression {
public:
    int a;

    Const(int b) : a(b) {
        prt = 33;
    }

    int Evaluate() const {
        return a;
    }

    // Преобразование в строку
    std::string ToString() const {
        return std::to_string(a);
    }

    // Деструктор
    ~Const() {}
};

// наследование суммы
class Sum : public Expression {
public:
    std::shared_ptr<Expression> left, right;

    Sum(ExpressionPtr &l, ExpressionPtr &r)
            : left(std::dynamic_pointer_cast<Expression>(l)),
            right(std::dynamic_pointer_cast<Expression>(r)) {
        prt = 2;
    }

    int Evaluate() const {
        return left->Evaluate() + right->Evaluate();
    }

    std::string ToString() const {
        return left->ToString() + " + " + right->ToString();
    }

    ~Sum() {
        left->~Expression();
        right->~Expression();
    }
};

class Product : public Expression {
public:
    std::shared_ptr<Expression> left, right;

    Product(ExpressionPtr &l, ExpressionPtr &r)
            : left(std::dynamic_pointer_cast<Expression>(l)),
            right(std::dynamic_pointer_cast<Expression>(r)) {
        prt = 33;
    }

    int Evaluate() const {
        return left->Evaluate() * right->Evaluate();
    }

    std::string ToString() const {
        if (left->prt > right->prt) {
            return left->ToString() + " * (" + right->ToString() + ')';
        } else if (left->prt < right->prt) {
            return '(' + left->ToString() + ") * " + right->ToString();
        } else if (left->prt == 2) {
            return '(' + left->ToString() + ") * (" + right->ToString();
        } else {
            return left->ToString() + " * " + right->ToString();
        }
    }

    ~Product() {
        left->~Expression();
        right->~Expression();
    }
};

ExpressionPtr Sum(ExpressionPtr a, ExpressionPtr b) {
    return ExpressionPtr(new class Sum(a, b));
}

ExpressionPtr Product(ExpressionPtr a, ExpressionPtr b) {
    return ExpressionPtr(new class Product(a, b));
}

ExpressionPtr Const(int x) {
    return ExpressionPtr(new class Const(x));
}


int main() {
    ExpressionPtr ex1 = Sum(Product(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
}