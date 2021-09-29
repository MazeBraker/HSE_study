n = int(input())
mass = []
i = 1
while i != n:
    if i * 3 <= n:
        i *= 3
        mass.append(i)
    elif i * 2 <= n:
        i *= 2
        mass.append(i)
    elif i + 1 <= n:
        i += 1
        mass.append(i)
    if i == n:
        break
print(len(mass))
print(1, sep=" ", *mass)
