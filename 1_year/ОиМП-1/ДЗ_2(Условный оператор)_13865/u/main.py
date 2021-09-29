a = int(input())
b = int(input())
c = int(input())
d = int(input())
if a == 0 and b == 0:
    print('INF')
elif a * (-b // a) + b == 0 and c * (-b // a) + d != 0:
    print(-b // a)
else:
    print('NO')
