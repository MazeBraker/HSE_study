p = float(input())
x = int(p)
print(x, end=' ')
p *= 100
a = p % 100
print(int(a + 0.0001))
