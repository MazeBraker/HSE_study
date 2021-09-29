def power(a, n):
    k = 1
    for i in range(abs(n)):
        k *= a
    if n >= 0:
        return k
    else:
        return 1 / k


a = float(input())
n = int(input())
print(power(a, n))