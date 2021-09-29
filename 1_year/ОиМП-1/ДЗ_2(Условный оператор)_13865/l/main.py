x1 = int(input())
y1 = int(input())
x2 = int(input())
y2 = int(input())
if y1 < y2 and x1 + y1 <= x2 + y2 and (x2 + y2) % 2 == 0:
    print('YES')
else:
    print('NO')