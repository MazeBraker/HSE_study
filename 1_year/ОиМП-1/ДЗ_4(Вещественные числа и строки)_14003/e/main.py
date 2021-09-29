p = float(input())
x = int(input())
y = int(input())
k = int(input())
s = x * 100 + y
i = 1
while i <= k:
    s += s * p / 100
    s = int(s // 100) * 100 + int(s % 100)
    i += 1
print(int(s // 100), int(s % 100))
