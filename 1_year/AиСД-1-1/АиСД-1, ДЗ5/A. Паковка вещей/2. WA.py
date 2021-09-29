N = int(input())
INF = 10 ** 10
F = [0] * (N + 1)
for i in range(1, N + 1):
    F[i] = F[i - 1] + 1
    j = 2
    while j ** 3 <= i:
        if F[i - j ** 3] < F[i]:
            F[i] = F[i - j ** 3] + 1
        j += 1
print(F[N])
print(F)
i = 0
while True:
    if F[N] == 1:
        print(int(pow(N + 1, 1 / 3)))
        break
    if F[N] - F[N - i] == 1 and pow(int(round(pow(i, 1 / 3))), 3) == i:
        print(int(pow(i, 1 / 3)), end=' ')
        N = N - i
        i = 0
    i += 1
