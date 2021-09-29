N = int(input())
F = [0] * (N + 1)
ans = [0] * (N + 1)

q = 1
while q ** 3 < N + 1:  # вспомогательный массив
    F[q ** 3] = 1  # 1 на месте точных кубов
    ans[q ** 3] = q  # точные кубы
    q += 1
# print(ans)
# print(F)

for i in range(2, N + 1):
    if F[i] == 0:
        j = 1
        F[i] = F[i - 1] + 1
        ans[i] = j
        while j ** 3 <= i:  # Проверяем можно ли попасть в эту клетку использую куб не превосходящий числа
            if F[i - j ** 3] < F[i]:
                F[i] = F[i - j ** 3] + 1  # Если да, и это быстрее чем добавление 1 из пред,то перезаписываем
                ans[i] = j
            j += 1
print(F[N])
# print(F)
# print(ans)
res = []
while N > 0:
    # print(i)
    res.append(ans[N])  # обязательно входит в это число
    N = N - (ans[N] ** 3)  # обратный ход
print(*reversed(res))
