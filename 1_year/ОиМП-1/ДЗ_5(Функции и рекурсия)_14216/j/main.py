def IsPrime(n):
    i = 2
    while i <= n ** 0.5:
        if n % i == 0:
            print('NO')
            return 0
        i += 1
    print('YES')


n = int(input())
IsPrime(n)
