myList = list(map(int, input().split()))
myList.sort()
max1 = myList[-1]
max2 = myList[-2]
min1 = myList[0]
min2 = myList[1]
if max1 * max2 > min1 * min2:
    print(min(max1, max2), max(max1, max2))
else:
    print(min(min1, min2), max(min1, min2))
