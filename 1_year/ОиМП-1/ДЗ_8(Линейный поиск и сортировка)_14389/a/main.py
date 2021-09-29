def IsAscending(list):
    for i in range(0, len(list)):
        if i != 0 and list[i] <= list[i - 1]:
            return 0
    return 1


if IsAscending(list(map(int, input().split()))):
    print('YES')
else:
    print('NO')
