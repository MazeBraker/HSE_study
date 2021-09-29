a = list(map(int, input().split()))
min = 0
for i in range(0, len(a)):
    if a[i] > 0:
        min = a[i]
        break
for i in range(0, len(a)):
    if a[i] < min and (a[i] > 0):
        min = a[i]
print(min)
