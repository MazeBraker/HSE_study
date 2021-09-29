i, j = map(int, input().split())
if i > j or j > i:
    i = i + j - 1
    print(i)
else:
    print(0)
