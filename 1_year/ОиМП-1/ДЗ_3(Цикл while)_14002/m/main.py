x = int(input())
i = 0
while x != 0:
    y = int(input())
    if y != 0 and x < y:
        i += 1
    x = y
print(i)
