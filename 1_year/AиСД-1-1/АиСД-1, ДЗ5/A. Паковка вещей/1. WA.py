def power(a, k):
    if k == 0:
        return 1
    elif k == 1:
        return a
    elif k % 2 != 0:
        return a * power(a, k - 1)
    elif k % 2 == 0:
        return power(a * a, k / 2)


k = 3
a = 0
n = int(input())
for i in range(n + 1):
    if power(a, k) >= n:
        break
    a += 1
print(i)
