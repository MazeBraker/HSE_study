def ipis(a, b):
    return abs(a) + abs(b) <= 1


a = float(input())
b = float(input())
if ipis(a, b):
    print('YES')
else:
    print('NO')
