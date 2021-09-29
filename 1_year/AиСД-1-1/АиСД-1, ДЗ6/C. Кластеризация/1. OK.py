n = int(input())
s = list(map(int, input().split()))
s = sorted(s)
ans = -100
A = 0
if n == 1:
    print(0)
else:
    for i in range(1, len(s)):
        A = i * (s[i] - s[i - 1])
        res = A * (len(s) - i)
        if res > ans:
            ans = res
    print(ans)
