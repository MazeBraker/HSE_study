a = int(input())
b = int(input())
c = int(input())
d = int(input())
if a < 1 or b < 1 or c < 1 or d < 1:
    print('NO')
elif a > 8 or b > 8 or c > 8 or d > 8:
    print('NO')
elif ((a - b) % 2 == 0 or (b - a) % 2 == 0) and \
        ((c - d) % 2 == 0 or (d - c) % 2 == 0):
    print('YES')
elif ((a - b) % 2 != 0 or (b - a) % 2 != 0) and \
        ((c - d) % 2 != 0 or (d - c) % 2 != 0):
    print('YES')
else:
    print('NO')
