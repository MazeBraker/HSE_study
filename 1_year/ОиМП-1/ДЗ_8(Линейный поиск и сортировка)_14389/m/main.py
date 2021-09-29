def merge(a, b):
    list = []
    r = 0
    w = 0
    while r < len(a) and w < len(b):
        if a[r] > b[w]:
            list.append(b[w])
            w += 1
        elif a[r] <= b[w]:
            list.append(a[r])
            r += 1
    while w < len(b) or r < len(a):
        if w < len(b):
            list.append(b[w])
            w += 1
        else:
            list.append(a[r])
            r += 1
    return list


a = list(map(int, input().split()))
b = list(map(int, input().split()))
print(*merge(a, b))
