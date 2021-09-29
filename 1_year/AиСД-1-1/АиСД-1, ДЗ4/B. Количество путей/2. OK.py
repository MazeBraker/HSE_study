n, k = map(int, input().split())
denied = list(map(int, input().split()))
C = [0] * (n + 1)  # колово способов для каждой клетки
C[1] = 1
for i in range(2, n + 1):
    if denied[i - 1] == 0:  # если пустая,то нет смысла считать пути через нее
        C[i] = 0
    else:
        C[i] = sum(C[max(0, i - k):i])
print(C[n] % 1000000007)
