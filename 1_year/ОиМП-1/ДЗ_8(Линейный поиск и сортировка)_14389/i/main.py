S, N = map(int, input().split())
data = sorted([int(input()) for i in range(N)])
k = 0
for i in range(len(data)):
    if S - data[i] > 0:
        S -= data[i]
        k += 1
        continue
    else:
        break
print(k)
