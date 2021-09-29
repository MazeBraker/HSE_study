n, m = map(int, input().split())
a = set([int(input()) for i in range(n)])
b = set([int(input()) for i in range(m)])
c = a & b
a = a - c
b = b - c
print(len(c))
print(*sorted(c))
print(len(a))
print(*sorted(a))
print(len(b))
print(*sorted(b))
