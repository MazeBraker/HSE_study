N = list(map(int, input().split()))
np = list(map(int, input().split()))
N = sorted(N)
np.sort(reverse=True)
sum = 0
for i in range(len(N)) and range(len(np)):
    sum += N[i] * np[i]
print(sum)
