n = int(input())
x = float(input())
s = 0
while n + 1 > 0:
    n1 = float(input())
    if n != 0:
        s = (s + n1) * x
    else:
        s = s + n1
    n -= 1
print(s)
