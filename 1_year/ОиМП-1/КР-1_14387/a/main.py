a = int(input())
b = int(input())
c = int(input())
d = int(input())
a = a * 100
c = c * 100
k = (d - b + (c - a) % 100) // 100
f = (d - b + (c - a) % 100) % 100
print((c - a) // 100 + k, f)