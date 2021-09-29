a = int(input())
b = int(input())
c = int(input())
d = int(input())
if a >= 0 and b >= 0 and c >= 0 and d >= 0:
    print('YES')
elif a <= 0 and b <= 0 and c <= 0 and d <= 0:
    print('YES')
elif a <= 0 and b >= 0 and c <= 0 and d >= 0:
    print('YES')
elif a >= 0 and b <= 0 and c >= 0 and d <= 0:
    print('YES')
else:
    print('NO')
