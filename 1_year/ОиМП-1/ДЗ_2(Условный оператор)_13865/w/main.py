a1 = int(input())
b1 = int(input())
a2 = int(input())
b2 = int(input())
a3 = int(input())
b3 = int(input())
if (b1 >= a2 and b2 >= a1 and (b3 >= a1 or b3 >= a2) and (a3 <= b1 or a3 <= b2)) or\
        (a1 <= b3 and a3 <= b1 and (a2 <= b1 or a2 <= b3) and (b2 >= a1 or b2 >= a3)):
    print(0)
elif 0 < a3 - b2 <= b1 - a1 or 0 < a2 - b3 <= b1 - a1 or a3 <= b2 and a2 <= b3:
    print(1)
elif 0 < a3 - b1 <= b2 - a2 or 0 < a1 - b3 <= b2 - a2 or a3 <= b1 and a1 <= b3:
    print(2)
elif 0 < a2 - b1 <= b3 - a3 or 0 < a1 - b2 <= b3 - a3 or a1 <= b2 and a2 <= b1:
    print(3)
else:
    print(-1)