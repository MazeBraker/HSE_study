len_b, cnt_blocks = map(int, input().split())  # длина лавочки и кол-во блоков
leg_place = list(sorted(map(int, input().split())))  # лист из ног > 0
center = len_b // 2
for i in range(len(leg_place)):
    # попали в центр (1 ножка)
    if leg_place[i] == center and len_b % 2 == 1:
        print(leg_place[i])
        break
    # если эта ножка дальше центра, то предыдущая перед ним -> достаточно только 2 ножки
    elif leg_place[i] >= center:
        print(leg_place[i - 1], leg_place[i])
        break