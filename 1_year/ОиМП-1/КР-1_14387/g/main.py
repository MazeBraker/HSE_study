a = input()
hh = int(a[:2])
mm = int(a[3:])
m1 = mm % 10
m2 = mm // 10
if hh == 0:
    print('12', ':', m2, m1, ' a.m.', sep='')
elif hh == 12 and mm > 0:
    print(hh, ':', m2, m1, ' p.m.', sep='')
elif hh == 12 and mm == 0:
    print(hh, ':', m2, m1, ' p.m.', sep='')
elif 0 <= hh < 12:
    print(hh, ':', m2, m1, ' a.m.', sep='')
elif 12 < hh <= 23:
    print(hh - 12, ':', m2, m1, ' p.m.', sep='')