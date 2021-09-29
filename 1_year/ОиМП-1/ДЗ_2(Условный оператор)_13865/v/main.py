k = int(input())
m = int(input())
n = int(input())
if n <= k:
    print(m * 2)
elif n * 2 % k == 0:
    print(m * 2*n // k)
else:
    print(m * (2*n // k + 1))
