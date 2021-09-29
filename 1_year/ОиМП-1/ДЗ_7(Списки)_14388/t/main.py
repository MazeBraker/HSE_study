a = [int(i) for i in input().split()]
k = []
for i in range(0, len(a)):
    if a.count(a[i]) == 1:
        k.append(a[i])
print(*k)
