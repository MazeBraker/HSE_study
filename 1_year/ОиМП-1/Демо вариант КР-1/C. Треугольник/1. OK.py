n = int(input())
a = int(input())
b = n
i = 0
c = -277
while n != 0:
    n = int(input())
    if n == 0:
        break
    c = n
    if a > b and a > c:
        i += 1
    b, a = a, c
print(i)
