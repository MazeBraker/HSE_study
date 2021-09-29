myset = list(map(int, input().split()))
a = set()
for elem in myset:
    if elem in a:
        print('YES')
    else:
        print('NO')
        a.add(elem)