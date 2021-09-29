n = int(input())
a = 1
b = 1
c = 0
k = 1
while True:
    a = c + b
    c, b = b, a
    k += 1
    if n == a:
        print(k)
        break
    if a > n:
        print(-1)
        break