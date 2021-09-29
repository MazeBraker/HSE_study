now = int(input())
nowMin = now
while now != 0:
    if now > nowMin:
        nowMin = now
    now = int(input())
print(nowMin)
