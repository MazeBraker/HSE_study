n = int(input())
n = n * 45 + n // 2 * 5 + (n + 1) // 2 * 15
print(n // 60 + 9, n % 60)
