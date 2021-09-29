a = [int(i) for i in input().split()]
k = -332
q = -228
for i in range(len(a)):
    if a.count(a[i]) > k:
        k = a.count(a[i])
        q = i
print(a[q])
