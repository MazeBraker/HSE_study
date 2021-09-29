from sys import stdin
from copy import deepcopy


class MatrixError(BaseException):
    def __init__(self, matrix1, matrix2):
        self.matrix1 = matrix1
        self.matrix2 = matrix2


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
        if Matrix.size(Matrix(self.list)) == Matrix.size(Matrix(mtr.list)):
            for row in range(len(self.list)):
                for i in range(len(self.list[row])):
                    rows[row][i] += mtr.list[row][i]
            return Matrix(rows)
        else:
            error = MatrixError(self, mtr)
            raise error

    # __mul__ принимающий число типа int или float и возвращающий матрицу, умноженную на скаляр
    def __mul__(self, n):
        rows = deepcopy(self.list)
        for row in range(len(self.list)):
            for i in range(len(self.list[row])):
                rows[row][i] *= n
        return Matrix(rows)

    __rmul__ = __mul__

    def transpose(self):
        s = Matrix.size(Matrix(self.list))
        result = [[0] * s[0]] * s[1]
        for i in range(s[1]):
            for j in range(s[0]):
                result[i][j] = self.list[j][i]
        self.arr = result
        return Matrix(result)

    def transposed(self):
        result = list(zip(*self.arr))
        result = list(map(list, result))
        return Matrix(result)


# exec(stdin.read())

if __name__ == "__main__":
    # Task 3 check 1
    # Check exception to add method
    m1 = Matrix([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
    m2 = Matrix([[0, 1, 0], [20, 0, -1], [-1, -2, 0]])
    print(m1 + m2)

    m2 = Matrix([[0, 1, 0], [20, 0, -1]])
    try:
        m = m1 + m2
        print('WA\n' + str(m))
    except MatrixError as e:
        print(e.matrix1)
        print(e.matrix2)
    # Task 3 check 2
    m = Matrix([[10, 10], [0, 0], [1, 1]])
    print(m)
    m1 = m.transpose()
    print(m)
    print(m1)

