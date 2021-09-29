from sys import stdin
from copy import deepcopy


class Matrix:
    # Конструктор от списка списков.
    def __init__(self, list):
        self.list = deepcopy(list)

    # Метод __str__ переводящий матрицу в строку.
    def __str__(self):
        rows = []
        for row in self.list:
            rows.append('\t'.join(map(str, row)))
        return '\n'.join(rows)

    # Метод size без аргументов, возвращающий кортеж вида (число строк, число столбцов)
    def size(self):
        return len(self.list), len(self.list[0])

    # __add__ принимающий вторую матрицу того же размера и возвращающий сумму матриц
    def __add__(self, mtr):
        rows = deepcopy(self.list)
        for row in range(len(self.list)):
            for i in range(len(self.list[row])):
                rows[row][i] += mtr.list[row][i]
        return Matrix(rows)

    # __mul__ принимающий число типа int или float и возвращающий матрицу, умноженную на скаляр
    def __mul__(self, n):
        rows = deepcopy(self.list)
        for row in range(len(self.list)):
            for i in range(len(self.list[row])):
                rows[row][i] *= n
        return Matrix(rows)

    __rmul__ = __mul__


# exec(stdin.read())

if __name__ == "__main__":
    # Task 2 check 1
    m = Matrix([[10, 10], [0, 0], [1, 1]])
    print(m.size())
    # Task 2 check 2
    m1 = Matrix([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
    m2 = Matrix([[0, 1, 0], [20, 0, -1], [-1, -2, 0]])
    print(m1 + m2)
    # Task 2 check 3
    m = Matrix([[1, 1, 0], [0, 2, 10], [10, 15, 30]])
    alpha = 15
    print(m * alpha)
    print(alpha * m)
