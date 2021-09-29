def ipis(x, y, x1, y1, r):
    return (x - x1) ** 2 + (y - y1) ** 2 <= r * r


x = float(input())
y = float(input())
x1 = float(input())
y1 = float(input())
r = float(input())
if ipis(x, y, x1, y1, r):
    print('YES')
else:
    print('NO')