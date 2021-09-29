a = int(input())
b = int(input())
c = 0
while True:
    if a % 2 == 0 and a // 2 >= b:
        c = a // 2
        print(":2")
    elif a % 2 != 0 and a - 1 >= b:
        c = a - 1
        print("-1")
    elif a % 2 == 0 and a - 1 >= b:
        c = a - 1
        print("-1")
    a = c
    if a == b:
        break
