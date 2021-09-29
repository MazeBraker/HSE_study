n = int(input())
a = n // 10 ** 5
b = n // 10 ** 4 % 10
c = n // 10 ** 3 % 10
d = n // 10 ** 2 % 10
e = n // 10 % 10
f = n % 10
a = a * 2
c = c * 2
e = e * 2
if a > 9:
    a = a - 9
if c > 9:
    c = c - 9
if e > 9:
    e = e - 9
if (a + b + c + d + e + f) % 10 == 0:
    print('YES')
else:
    print('NO')
