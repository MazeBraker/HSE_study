a = int(input())
b = int(input())
c = int(input())
d = int(input())
if a < 1 or b < 1 or c < 1 or d < 1:
    print('NO')
elif a > 8 or b > 8 or c > 8 or d > 8:
    print('NO')
elif c == a or c == a + 1 or c == a - 1:
    if d == b or d == b + 1 or d == b - 1:
        print('YES')
    else:
        print('NO')
else:
    print('NO')
