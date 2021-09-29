from copy import deepcopy


class MatrixError(BaseException):
    """Matrix class error catcher. """

    def __init__(self, first, second):
        self.matrix1 = first
        self.matrix2 = second


class Matrix:
    """ Matrix class for coursera task purposes. """

    def __init__(self, arr: list):
        my_arr = deepcopy(arr)
        self.matrix = my_arr

    def __repr__(self):
        return self.matrix

    def __len__(self):
        return len(self.matrix)

    def __str__(self):
        """ Returns a string where matrix represented as rows and columns. """
        matrix_string = ''
        for i in self.matrix:
            matrix_string += "\t".join(map(str, i))
            matrix_string += "\n"
        return matrix_string.strip()

    def __eq__(self, other):
        """ Check equality of two matrices. """
        for i in range(len(self.matrix)):
            if self.matrix[i] == other.matrix[i]:
                continue
            return False
        return True

    def __add__(self, other):
        """ Sum of two matrices. + Exception(matrices size equality). """
        if self.nesting() != other.nesting():
            raise MatrixError(self, other)
        m_sum = []
        for i in range(len(self.matrix)):
            m_sum.append(list([0] * (len(self.matrix[i]))))
            for j in range(len(self.matrix[i])):
                m_sum[i][j] = self.matrix[i][j] + other.matrix[i][j]
        return Matrix(m_sum)

    def __mul__(self, other: int):
        """ Multiplying of a matrix by an integer. """
        m_mul = []
        for i in range(len(self.matrix)):
            m_mul.append(list([0] * (len(self.matrix[i]))))
            for j in range(len(self.matrix[i])):
                m_mul[i][j] = self.matrix[i][j] * other
        return Matrix(m_mul)

    __rmul__ = __mul__  # Makes order of __mul__ arguments irrelevant.

    def size(self):
        """ Returns tuple of the number of matrix rows and columns. """
        return len(self.matrix), len(self.matrix[0])

    def nesting(self):
        return list(len(self.matrix[i]) for i in range(len(self.matrix)))

    def is_square(self):
        """ Check that the matrix is square. """
        for i in self.nesting():
            if len(self.nesting()) != i:
                return False
        return True

    def transpose(self):
        """ Transpose matrix object itself. """
        self.matrix = list(map(list, zip(*self.matrix)))
        return self

    @staticmethod
    def transposed(m):
        """ Matrix transpose. Returns new object. """
        matrix = Matrix(m.matrix).transpose()
        return matrix

if __name__ == "__main__":
    # Task 5 check 1
    m = Matrix([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
    print(m.solve([1, 1, 1]))