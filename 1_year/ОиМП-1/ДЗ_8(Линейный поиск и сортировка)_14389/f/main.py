n = map(int, input().split())
index = [0] * 101
for n in n:
    index[n] += 1
for number in range(101):
    print((str(number) + ' ') * index[number], end='')
