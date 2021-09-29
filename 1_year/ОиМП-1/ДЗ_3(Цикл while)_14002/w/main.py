n = int(input())
lm1 = 0
lm2 = 0
r = 0
k = 0
t = 0
prev = 0
cur = n
fut = 0
i = 0
while n != 0:
    i += 1
    if cur != 0 and prev != 0 and fut != 0 and prev < cur and fut < cur:
        lm2 = lm1
        lm1 = cur
        if lm2 == 0:
            k = i
        else:
            t = i - k
            k = i
            if r > t or r == 0:
                r = t
    n = int(input())
    if prev == 0:
        prev = cur
        cur = n
    elif fut == 0:
        fut = n
    else:
        prev = cur
        cur = fut
        fut = n
print(r)