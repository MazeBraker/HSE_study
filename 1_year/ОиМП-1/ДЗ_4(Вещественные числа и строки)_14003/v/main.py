a = float(input())
b = float(input())
c = float(input())
d = float(input())
e = float(input())
f = float(input())
# последовательно обрабатываю все случаи из условия
if a * d - b * c != 0:
    x = (e * d - b * f) / (a * d - b * c)
    y = (a * f - e * c) / (a * d - b * c)
    print(2, x, y)
elif b != 0 and a != 0 and c * e == a * f:
    print(1, - a / b, e / b)
elif b == 0 and a != 0 and c * e == a * f:
    print(3, e / a)
elif a == 0 and b != 0 and d * e == b * f:
    print(4, e / b)

elif d != 0 and c != 0 and c * e == a * f:
    print(1, - c / d, f / d)
elif d == 0 and c != 0 and c * e == a * f:
    print(3, f / c)
elif c == 0 and d != 0 and d * e == b * f:
    print(4, f / d)

elif a == 0 and b == 0 and c == 0 and d == 0 and e == 0 and f == 0:
    print(5)
else:
    print(0)
