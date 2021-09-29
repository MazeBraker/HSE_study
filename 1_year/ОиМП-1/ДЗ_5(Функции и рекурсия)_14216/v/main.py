def lagrange(n, level):
    if level == 0:
        return "NO"
    sqrtn = int(n ** 0.5)
    if sqrtn * sqrtn == n:
        return str(sqrtn)
    while sqrtn > 0:
        if lagrange(n - sqrtn * sqrtn, level - 1) != "NO":
            return str(sqrtn) + " " + lagrange(n - sqrtn * sqrtn, level - 1)
        sqrtn -= 1
    return "NO"


n = int(input())
print(lagrange(n, 4))