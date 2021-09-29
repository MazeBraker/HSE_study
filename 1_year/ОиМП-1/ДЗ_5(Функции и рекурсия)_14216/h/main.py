def IsPointInArea(x, y):
    q = -x <= y
    w = 2 * x + 2 <= y
    e = (x + 1) ** 2 + (y - 1) ** 2 <= 2 * 2
    r = -x >= y and 2 * x + 2 >= y
    t = (x + 1) ** 2 + (y - 1) ** 2 >= 2 * 2
    return (q and w and e) or (r and t)


x = float(input())
y = float(input())
if IsPointInArea(x, y):
    print('YES')
else:
    print('NO')