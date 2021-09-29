n = int(input())
a = 1
b = 1
c = 0
k = 1
while k < n:
    a = c + b
    c, b = b, a
    k += 1
print(a)