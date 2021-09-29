a = [int(i) for i in input().split()]
k = 0
for i in range(len(a)):
    for j in range(i + 1, len(a)):
        if a[i] == a[j]:
            k += 1
print(k)
