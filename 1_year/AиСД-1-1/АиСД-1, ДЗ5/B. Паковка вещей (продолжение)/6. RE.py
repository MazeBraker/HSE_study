import sys


def MinOfCubedDP(k):
    DP = [0] * (k + 1)
    j = 1
    t = 1
    DP[0] = 0
    for i in range(1, k + 1):
        DP[i] = sys.maxsize
        # Пока нынешний идеальный куб
        # меньше текущего элемента
        while j <= i:
            # Если идеальный куб
            if j == i:
                DP[i] = 1
                # i = (i - 1) + 1^3
            elif DP[i] > DP[i - j]:
                DP[i] = DP[i - j] + 1
                # Следующий идеальный куб
            t += 1
            j = pow(t, 3)
            # Повторная инициализация для следующего элемента
        t = j = 1
    return DP[k]


n = int(input())
print(MinOfCubedDP(n))
