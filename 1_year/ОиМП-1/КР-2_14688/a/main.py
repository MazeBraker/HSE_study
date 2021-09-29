def Election(x, y, z):
    if x + y + z >= 2:
        return 1
    return 0


x, y, z = list(map(int, input().split()))
print(Election(x, y, z))
