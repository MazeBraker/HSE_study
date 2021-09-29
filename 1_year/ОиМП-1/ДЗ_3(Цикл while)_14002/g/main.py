x = int(input())
y = int(input())
i = 1
while x < y:
    x = x + x / 10
    i = i + 1
print(i)
