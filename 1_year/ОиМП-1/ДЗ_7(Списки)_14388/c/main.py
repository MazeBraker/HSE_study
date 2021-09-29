a = input().split()
k = 0
for i in range(0, len(a)):
    if int(a[i]) > 0:
        k += 1
print(k)
