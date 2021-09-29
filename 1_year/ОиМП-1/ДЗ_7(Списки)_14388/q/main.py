a = [int(i) for i in input().split()]
b = int(input())
for i in range(b + 1, len(a)):
    a[i - 1] = a[i]
a.pop(-1)
print(' '.join([str(i) for i in a]))
