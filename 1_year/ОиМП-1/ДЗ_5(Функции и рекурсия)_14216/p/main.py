a = int(input())
b = int(input())


def algos(a, b):
    if b == 0:
        return a
    else:
        return algos(b, a % b)


print(a // algos(a, b), b // algos(a, b))
