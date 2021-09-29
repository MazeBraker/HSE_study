n = int(input())
s = 0
for i in range(1, n):
    a = int(input())
    s += a
print(n * (n + 1) // 2 - s)
