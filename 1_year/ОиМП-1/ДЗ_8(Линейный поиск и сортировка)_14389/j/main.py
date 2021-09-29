size = int(input())
n = list(map(int, input().split()))
a = size
k = 0
n.sort()
for i in range(len(n)):
    if size == n[i]:
        k = 1
for i in range(len(n)):
    if a + 3 <= n[i]:
        a = n[i]
        k += 1
print(k)
