a = list(map(int, input().split()))
min = 10000000000000000000000000000000000
for i in range(0, len(a)):
    if a[i] < min and (a[i] % 2 != 0):
        min = a[i]
print(min)
