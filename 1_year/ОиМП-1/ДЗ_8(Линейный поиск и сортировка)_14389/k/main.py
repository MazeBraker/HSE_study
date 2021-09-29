n = int(input())
guys = [input().split() for i in range(n)]
for i in sorted(guys, key=lambda x: int(x[1]), reverse=True):
    print(i[0])
