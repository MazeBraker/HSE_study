participants = int(input())
cnt_stations = participants // 6
ostatok = participants % 6
if participants - cnt_stations * 6 == 0:
    print(6, '+6' * (cnt_stations - 1), sep='')

elif participants - cnt_stations * 6 == 5:
    print(5, '+6' * cnt_stations, sep='')

elif participants - (participants // 5) * 5 == 0:
    print(5, '+5' * (participants // 5 - 1), sep='')
elif participants - (participants // 5) * 5 == 4:
    print(4, '+5' * (participants // 5), sep='')

elif participants - participants // 4 * 4 == 0:
    print(4, '+4' * (participants // 4 - 1), sep='')
elif participants - (participants // 4) * 4 == 3:
    print(3, '+4' * (participants // 4), sep='')


elif participants - (participants // 3) * 3 == 0:
    print(3, '+3' * ((participants // 3) - 1), sep='')
elif participants - (participants // 3) * 3 == 2:
    print(2, '+3' * (participants // 3), sep='')

elif participants - (participants // 2) * 2 == 0:
    print(2, '+2' * (participants // 2 - 1), sep='')
elif participants - (participants // 2) * 2 == 1:
    print(1, '+2' * (participants // 2), sep='')
