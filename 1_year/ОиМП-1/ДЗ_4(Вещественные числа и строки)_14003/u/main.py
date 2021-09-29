from math import sqrt

a, b, c = float(input()), float(input()), float(input())

d = b ** 2 - 4 * a * c
if a == b == c == 0:
    print(3)
elif d < 0 or (a == b == 0 and c != 0):
    print(0)
elif a == 0:
    print(1, -c / b)
elif d == 0:
    print(1, (-b) / (2 * a))
elif d > 0:
    root1 = round(((-b) - sqrt(d)) / (2 * a), 6)
    root2 = round(((-b) + sqrt(d)) / (2 * a), 6)
    if root1 < root2:
        print(2, root1, root2)
    else:
        print(2, root2, root1)