a = int(input())


def p(a):
    if a == 0:
        return 0
    elif a == 1:
        return 1
    else:
        return p(a - 1) + p(a - 2)


print(p(a))
