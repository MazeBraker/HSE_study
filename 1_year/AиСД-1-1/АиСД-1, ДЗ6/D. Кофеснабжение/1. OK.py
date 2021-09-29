n = int(input())
a = list(map(int, input().split()))
m = int(input())
b = list(map(int, input().split()))
for x in b:
    left = -1
    right = len(a)
    # левый бинпоиск, который ищет левую границу
    while right - left > 1:
        middle = (right + left) // 2
        if a[middle] < x:
            left = middle
        else:
            right = middle

    left_1 = -1
    right_1 = len(a)
    # правый бинпоиск, который ищет правый границу
    while right_1 - left_1 > 1:
        middle = (right_1 + left_1) // 2
        if a[middle] <= x:
            left_1 = middle
        else:
            right_1 = middle

    if left == left_1 and right == right_1:
        print(0, 0)
        # возращение к следующей итерации с пропуском, что идет после него
        continue
    if right == left_1:
        print(right + 1, right + 1)
    else:
        print(right + 1, left_1 + 1)
