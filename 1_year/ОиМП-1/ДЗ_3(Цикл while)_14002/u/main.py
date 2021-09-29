prev = -100
cur = 1
num = 0
while True:
    s = int(input())
    if s == 0:
        break
    if prev == -100:
        num = 1
        cur = 1
    else:
        if s == prev:
            cur += 1
        else:
            cur = 1
    if cur > num:
        num = cur
    prev = s
print(num)
