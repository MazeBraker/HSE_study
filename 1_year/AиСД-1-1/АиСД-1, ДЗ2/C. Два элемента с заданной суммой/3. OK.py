from collections import deque

tail = deque()
N = int(input())
for i in range(N):
    a = input()
    if a[0] == '+':
        q, now = a.split()
        now = int(now)
        tail.append(now)
    if a[0] == "-":
        print(tail.popleft())
    if a[0] == "*":
        q, now = a.split()
        now = int(now)
        tail.append((len(tail) + 1) // 2, now)
