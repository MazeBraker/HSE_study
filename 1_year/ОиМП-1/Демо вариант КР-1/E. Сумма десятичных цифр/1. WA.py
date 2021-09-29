one = int(input())
two = int(input())
if two != 0:
    three = int(input())
    if three != 0:
        if two > one and two > three:
            i = 1
        else:
            i = 0
        now = int(input())
        while now != 0:
            one, two = two, one
            two, three = three, two
            three, now = now, three
            if two > one and two > three:
                i += 1
            now = int(input())
        print(i)
    else:
        print(0)
else:
    print(0)
