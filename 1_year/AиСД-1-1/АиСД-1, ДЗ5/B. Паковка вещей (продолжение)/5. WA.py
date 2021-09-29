def MinOfCubes(k):
    res = k
    for i in range(1, k + 1):
        if pow(i, 3) > k:
            return res
        res = min(res, MinOfCubes(k - pow(i, 3)) + 1)
    return res


num = int(input())
print(MinOfCubes(num))
