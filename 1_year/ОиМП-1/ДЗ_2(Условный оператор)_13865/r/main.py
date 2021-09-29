a1 = int(input())
b1 = int(input())
c1 = int(input())
a2 = int(input())
b2 = int(input())
c2 = int(input())
one = (a1 // a2) * (b1 // b2) * (c1 // c2)
two = (a1 // a2) * (b1 // c2) * (c1 // b2)
three = (a1 // b2) * (b1 // a2) * (c1 // c2)
four = (a1 // b2) * (b1 // c2) * (c1 // a2)
five = (a1 // c2) * (b1 // b2) * (c1 // a2)
six = (a1 // c2) * (b1 // a2) * (c1 // b2)
if six > five:
    five = six
if five > four:
    four = five
if four > three:
    three = four
if three > two:
    two = three
if two > one:
    one = two
print(one)
