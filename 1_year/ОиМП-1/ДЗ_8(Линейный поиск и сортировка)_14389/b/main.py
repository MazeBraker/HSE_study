a = list(map(int, input().split()))
max = -111111111
k = 0
for i in range(len(a)):
    if max <= a[i]:
        max = a[i]
        k = i
print(max, k)
