a = input().split()
k = 0
for i in range(1, len(a)):
    if int(a[i]) > int(a[i - 1]):
        print(a[i], end=' ')
