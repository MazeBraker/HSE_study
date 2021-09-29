a, b, c = list(map(int, input().split()))


def kungfoo(a, b, c, lst=""):
    res = ""
    if a > 0:
        res = res + kungfoo(a - 1, b, c, lst + "0")
    if b > 0:
        res = res + kungfoo(a, b - 1, c, lst + "1")
    if c > 0:
        res = res + kungfoo(a, b, c - 1, lst + "2")
    if (a == b == c == 0):
        return lst + "\n"

    return res


print(kungfoo(a, b, c))
