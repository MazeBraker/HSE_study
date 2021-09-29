def MinDivisor(n):
    i = 2
    while i <= n ** 0.5:
        if n % i == 0:
            return i
        i += 1
    return n


n = int(input())
print(MinDivisor(n))
