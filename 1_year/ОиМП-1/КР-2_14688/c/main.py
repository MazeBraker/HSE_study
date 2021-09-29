n = int(input())
print("+".join("{}*{}".format(i, i + 1) for i in range(1, n)), end="=")
sum = 0
for k in range(1, n):
    sum += k * (k + 1)
print(sum)