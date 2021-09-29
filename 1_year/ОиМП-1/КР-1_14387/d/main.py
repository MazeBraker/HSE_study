a = int(input())
c = int(input())
b = int(input())
d = int(input())
if (abs(a - b) == 2) and (abs(c - d) == 1) or \
        ((abs(a - b) == 1) and (abs(c - d) == 2)):
    print('YES')
else:
    print('NO')
