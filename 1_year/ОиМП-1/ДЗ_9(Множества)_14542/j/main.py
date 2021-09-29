a, b, c, d = [int(i) for i in input().split()]
e = set(range(min(a, b), max(a, b) + 1))
f = set(range(min(c, d), max(c, d) + 1))
common = len(e & f)
print(common)
