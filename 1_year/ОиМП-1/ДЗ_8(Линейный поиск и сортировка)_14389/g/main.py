n = int(input())
maxtaps = list(map(int, input().split()))
k = int(input())
tapseq = list(map(int, input().split()))
taps = [0] * n
for i in tapseq:
    taps[i - 1] += 1
for i in range(n):
    if maxtaps[i] < taps[i]:
        print('YES')
    else:
        print('NO')