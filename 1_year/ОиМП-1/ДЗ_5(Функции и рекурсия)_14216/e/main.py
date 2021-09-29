def ipis(a, b):
    return abs(a) <= 1 and abs(b) <= 1


a = float(input())
b = float(input())
if ipis(a, b):
    print('YES')
else:
    print('NO')
