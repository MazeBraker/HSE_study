n = int(input())
nowMax = n
k = 0
while n != 0:
    if n > nowMax:
        nowMax = n
        k = 0
    if n == nowMax:
        k += 1
    n = int(input())
print(k)
