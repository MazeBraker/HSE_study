n, k = map(int, input().split())
denied = list(map(int, input().split()))
C = [0] * (n + 1)  # колово способов для каждой клетки
C[1] = 1
otkenzholdar = [0] * (n + 1)
otkenzholdar[1] = 1
for i in range(1, n + 1):
    if denied[i - 1] != 0:  # если пустая,то нет смысла считать пути через нее
        otkenzholdar[i] += (C[i - 1]) % 1000000007
        if (i - k - 1) >= 0:
            otkenzholdar[i] -= C[i - k - 1] % 1000000007
    C[i] = (C[i - 1] + otkenzholdar[i]) % 1000000007
print(otkenzholdar[n] % 1000000007)
