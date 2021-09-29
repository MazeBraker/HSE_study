a = list(map(int, input().split()))
b = list(map(int, input().split()))
m1 = a[0]
m2 = a[1]
n1 = b[0]
n2 = b[1]
for i in range(m1, m2 + 1):
    for j in range(n1, n2 + 1):
        print(i, 'x', j, "=", i * j)
    print('')
