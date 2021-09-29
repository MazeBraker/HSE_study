n = int(input())
d = list(map(int, input().split()))
d.sort()
q = 0
for i in range(n):
    for j in range(i + 1, n):
        for k in range(j + 1, n):
            if d[i] + d[j] > d[k]:
                q += 1
print(q)
