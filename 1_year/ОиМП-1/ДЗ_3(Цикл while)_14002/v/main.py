n = int(input())
op, cur = 0, n
k, r = 1, 1
while n != 0:
    if n > cur:
        if op != 1:
            op = 1
            k = 2
        else:
            k += 1
        if r < k:
            r = k
    elif n == cur:
        op = 0
        k = 1
    else:
        if op != -1:
            op = -1
            k = 2
        else:
            k += 1
        if r < k:
            r = k
    cur = n
    n = int(input())
print(r)
