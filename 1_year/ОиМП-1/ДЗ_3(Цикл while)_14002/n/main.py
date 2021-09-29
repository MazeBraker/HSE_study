max1 = int(input())
max2 = int(input())
if max1 < max2:
    max1, max2 = max2, max1
n = int(input())
while n != 0:
    if n > max1:
        max2, max1 = max1, n
    elif n > max2:
        max2 = n
    n = int(input())
print(max2)
