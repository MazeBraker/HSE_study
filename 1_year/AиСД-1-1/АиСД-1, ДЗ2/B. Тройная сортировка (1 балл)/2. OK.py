from collections import deque

head = deque()
tail = deque()
N = int(input())
for i in range(N):
    a = input()
    if a[0] == '+':
        now = int(a[2])
        tail.append(now)
        if len(tail) >= len(head):
            head.append(tail.popleft())
    elif a[0] == '-':
        print(head.popleft())
        if len(head) <= len(tail):
            head.append(tail.popleft())
    elif a[0] == '*':
        now = int(a[2])
        if len(head) <= len(tail):
            head.appendleft(now)
        else:
            tail.append(now)
