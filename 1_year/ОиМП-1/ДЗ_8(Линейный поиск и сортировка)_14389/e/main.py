a = list(map(int, input().split()))
a.sort()
b = a[0] * a[1] * a[-1]
c = a[-1] * a[-2] * a[-3]
if b > c:
    print(a[0], a[-1], a[1])
else:
    print(a[-1], a[-2], a[-3])
