n = int(input())
a = int(input())
s = 0
while n != 0:
    s = (s + (n * a)) ** 0.5
    n = n - 1
    if n == 0:
        break
    s = (n * a + s) ** 0.5
    n = n - 1
print(s)
