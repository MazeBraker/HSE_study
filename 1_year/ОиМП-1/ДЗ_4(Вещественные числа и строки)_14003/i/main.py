a = float(input())
b = float(input())
c = float(input())
D = b ** 2 - 4 * a * c
if D > 0:
    x1 = (-b + D ** 0.5) / (2 * a)
    x2 = (-b - D ** 0.5) / (2 * a)
    if x1 > x2:
        print(x2, x1)
    else:
        print(x1, x2)
elif D == 0:
    x = -b / (2 * a)
    print(x)
