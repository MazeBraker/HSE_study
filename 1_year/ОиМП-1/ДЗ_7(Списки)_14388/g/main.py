a = list(map(int, input().split()))
j = 0
for i in range(1, len(a)):
    if a[i] > a[j]:
        j = i
print(a[j], j)
