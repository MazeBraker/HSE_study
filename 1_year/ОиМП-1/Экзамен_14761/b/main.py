size_n, num = map(int, input().split())
matrix = [list(map(int, input().split())) for i in range(size_n)]
# print(matrix)
for j in range(size_n):
    my_list = []
    for i in range(size_n):
        # идем по столбцу начальной матрицы
        my_list.append((abs(matrix[i][j] - num), matrix[i][j]))  # на первом месте модуль разницы, на втором само число
    my_list.sort()  # сортируем по 1 элементу(то есть модулю расстояния)
    for i in range(size_n):
        matrix[i][j] = my_list[i][1]  # меняем местами элементы в изначальной матрице
for i in range(size_n):
    print(*matrix[i])