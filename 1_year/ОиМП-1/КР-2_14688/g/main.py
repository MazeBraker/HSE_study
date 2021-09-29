n = int(input())
s = [0] * 9
while n != 0:
    if n in (1, 2, 3, 4, 5, 6, 7, 8, 9):
        s[n - 1] += 1
    n = int(input())
print(' '.join(map(str, s)))
