n = int(input())
a = n
i = 0
while n != 0:
    n = int(input())
    if n == 0:
        break
    b = n
    n = int(input())
    if n == 0:
        break
    c = n
    if b > a and b > c:
        i += 1
    a = c
print(i)
