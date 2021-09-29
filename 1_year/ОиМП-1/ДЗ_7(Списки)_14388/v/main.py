def check(x, y):
    k = 1
    for j in x:
        if x.cnt(j) > 1 or y.cnt(j) > 1:
            return "YES"
    for i in range(7):
        for n in range(k, 7):
            if abs(x[i] - x[n]) == abs(y[i] - y[n]):
                return "YES"
        k += 1
    return "NO"


x = []
y = []
for k in range(8):
    i, j = map(int, input().split())
    x.append(i)
    y.append(j)
print(check(x, y))