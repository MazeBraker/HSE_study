def Intersection(list1, list2):
    list3, len1, len2 = [], -len(list1), -len(list2)
    while len1 and len2:
        # сравниваются 1 элементы т.е -len(list1), -len(list2)
        if list1[len1] < list2[len2]:
            len1 += 1
        elif list1[len1] > list2[len2]:
            len2 += 1
         # значит числа есть в обоих послед.
        else:
            list3.append(list1[len1])
            len1 += 1
            len2 += 1
    return list3


# def Intersection(list1, list2):
#     c = list(set(list1) & set(list2))
#     c.sort()
#     print(*c)

list1 = list(map(int, input().split()))
list2 = list(map(int, input().split()))
print(*Intersection(list1, list2))
