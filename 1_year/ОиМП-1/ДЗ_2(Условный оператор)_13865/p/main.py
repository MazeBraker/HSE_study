a = int(input())
b = int(input())
c = int(input())
d = int(input())
e = int(input())
if b >= c:
    (b, c) = (c, b)
if a >= b:
    (a, b) = (b, a)
if b >= c:
    (b, c) = (c, b)
if d >= e:
    (d, e) = (e, d)
if d >= a and e >= b:
    print('YES')
else:
    print('NO')
