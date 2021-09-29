rows, columns = list(map(int, input().split()))
matrix_of_values = []
comp_matrix = []
greatest_val = 0
for i in range(rows):
    string = (list(map(int, input().split())))
    matrix_of_values.append(string)  # ввод нашей матрицы

for j in range(rows):
    comp_matrix.append([])
    for i in range(columns):
        comp_matrix[j].append(0)  # ввод нулевой матрицы

for i in range(rows):
    comp_matrix[i][0] = matrix_of_values[i][0]
for j in range(columns):
    comp_matrix[-1][j - 1] = matrix_of_values[-1][j - 1]

for i in range(rows - 1):
    for j in range(1, columns):
        if matrix_of_values[i][j] == 1:
            comp_matrix[i][j] = min(comp_matrix[i - 1][j - 1], comp_matrix[i][j - 1], comp_matrix[i - 1][j]) + 1
            greatest_val = max(greatest_val, comp_matrix[i][j])
            # беру минимум из элементов слево,сверху и по диаг слево + 1
            # тупо динамика)
print(greatest_val)
