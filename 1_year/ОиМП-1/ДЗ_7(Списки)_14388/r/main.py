lst = list(map(int, input().split()))
kC = list(map(int, input().split()))
lst.append(lst[-1])
for i in range(len(lst)-1, kC[0], - 1):
    lst[i] = lst[i-1]
else:
    lst[kC[0]] = kC[1]
print(*lst)