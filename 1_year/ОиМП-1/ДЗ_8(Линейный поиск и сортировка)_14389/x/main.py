n = int(input())
villages = list(map(int, input().split()))
m = int(input())
shelters = list(map(int, input().split()))
villages_tup = []
shelters_tup = []
for i in range(m):
    a = (i + 1, shelters[i])
    shelters_tup.append(a)
shelters_tup.sort(key=lambda x: x[1])


def nearest_shelter(dist):
    if dist < shelters_tup[0][1]:
        return shelters_tup[0][0]
    if dist > shelters_tup[-1][1]:
        return shelters_tup[-1][0]

    l = 0
    r = len(shelters_tup) - 1

    while r - l > 1:
        m = (r + l) >> 1
        if shelters_tup[m][1] < dist:
            l = m
        else:
            r = m

    if dist - shelters_tup[l][1] < shelters_tup[r][1] - dist:
        return shelters_tup[l][0]
    else:
        return shelters_tup[r][0]


resList = [nearest_shelter(v) for v in villages]
print(*resList)
