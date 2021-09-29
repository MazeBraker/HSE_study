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

# exec(stdin.read())

# if __name__ == "__main__":
#     m = Matrix([[1, 0], [0, 1]])
#     print(m)
#     m = Matrix([[2, 0, 0], [0, 1, 10000]])
#     print(m)
#     m = Matrix([[-10, 20, 50, 2443], [-5235, 12, 4324, 4234]])
#     print(m)
