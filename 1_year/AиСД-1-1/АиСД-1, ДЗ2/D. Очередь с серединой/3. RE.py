n, k = map(int, input().split())
A = list(map(int, input().split()))
lst = [0] * (n + 1 - k)
firstsum = 0
q = 1
for i in range(k):
    lst[0] += ((-1) ** i) * A[i] * (i + 1)
    firstsum += ((-1) ** i) * A[i]
for i in range(k, n):
    lst[q] = - lst[i - k] + firstsum + (k * A[i] * ((-1) ** (k + 1)))
    firstsum = -firstsum + A[i - k] + (A[i] * (-1) ** (k + 1))
    q += 1
print(*lst)
