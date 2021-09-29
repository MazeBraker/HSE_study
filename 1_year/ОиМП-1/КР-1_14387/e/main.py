now = int(input())
nowMax = now
nowMin = now
now1 = now
while now != 0:
    if now > nowMax:
        nowMax = now
    if now1 < nowMin:
        nowMin = now1
    now = int(input())
    now1 = now
print(nowMin, nowMax)
