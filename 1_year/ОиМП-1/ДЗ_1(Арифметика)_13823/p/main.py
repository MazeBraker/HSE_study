N = int(input())
print(N // 60 % 24, (N - N // 60 * 60) % 60)