import sys


def MinOfCubedDP(k):
    global arr
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
                arr = DP

            t += 1
            j = pow(t, 3)
            # Повторная инициализация для следующего элемента
        t = j = 1
    return DP[k]


n = int(input())
print(MinOfCubedDP(n))
# print(arr)
f = len(arr) - 1
for i in range(f):
    if n == 0:
        print(0)
        break
    if n == 1:
        print(1)
        break
    elif arr[f] == 1:
        print(int(f ** (1. / 3)))
        break
    elif arr[f] - arr[f - i] == 1:
        print(int(i ** (1. / 3)), end=' ')
        arr[f] = arr[f - i]
        i = 1
        if arr[f] == 1:
            print(int(f ** (1. / 3)), end='\n')
            break
