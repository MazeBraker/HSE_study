n = int(input())
i = 0
sum = 0
while 2 ** i <= n:
    sum = 2 ** i
    print(sum)
    i = i + 1
