def maxway(matrix, n, m):
    def maxsize(i, j):
        matrix[i][j] = 0
        result = 1
        # проверяю 4 соседей
        if i > 0 and matrix[i - 1][j]:
            result += maxsize(i - 1, j)
        if j > 0 and matrix[i][j - 1]:
            result += maxsize(i, j - 1)
        if i < len(matrix) - 1 and matrix[i + 1][j]:
            result += maxsize(i + 1, j)
        if j < len(matrix[0]) - 1 and matrix[i][j + 1]:
            result += maxsize(i, j + 1)
        return result

    # максимум
    csize = 0
    for i in range(n):
        for j in range(m):
            if matrix[i][j]:
                now = maxsize(i, j)
                if now > csize:
                    csize = now

    return csize


m, n = map(int, input().split())
matrix = []
for i in range(m):
    matrix.append(list(map(int, input().split())))
print(maxway(matrix, m, n))
