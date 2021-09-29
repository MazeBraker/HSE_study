from collections import deque

head = deque()
tail = deque()
N = int(input())
for i in range(N):
    a = input()
    if a[0] == '+':
        q, now = a.split()
        now = int(now)
        tail.append(now)
        if len(tail) > len(head):
            head.append(tail.popleft())
    elif a[0] == '-':
        print(head.popleft())
        if len(head) < len(tail):
            head.append(tail.popleft())
    elif a[0] == '*':
        q, now = a.split()
        now = int(now)
        if len(head) > len(tail):
            tail.appendleft(now)
        else:
            head.append(now)
