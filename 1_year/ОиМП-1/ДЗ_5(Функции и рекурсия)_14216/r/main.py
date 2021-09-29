n = int(input())
k = int(input())


def cnk(n, k):
    if k == 0:
        return 1
    elif k == n:
        return 1
    else:
        return cnk(n - 1, k - 1) + cnk(n - 1, k)


print(cnk(n, k))
