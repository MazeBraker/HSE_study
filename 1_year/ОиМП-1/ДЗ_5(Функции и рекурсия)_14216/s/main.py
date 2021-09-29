def sum():
    s = 0
    while True:
        n = int(input())
        if n == 0:
            return s
        s += n


print(sum())
