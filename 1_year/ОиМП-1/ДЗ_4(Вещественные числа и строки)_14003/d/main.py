p = float(input())
x = int(input())
y = int(input())
s = x * 100 + y
s = s + s * p / 100
print(int(s // 100), int(s % 100))
