a1 = int(input())
b1 = int(input())
c1 = int(input())
a2 = int(input())
b2 = int(input())
c2 = int(input())
if b1 >= c1:
    (b1, c1) = (c1, b1)
if a1 >= b1:
    (a1, b1) = (b1, a1)
if b1 >= c1:
    (b1, c1) = (c1, b1)
if b2 >= c2:
    (b2, c2) = (c2, b2)
if a2 >= b2:
    (a2, b2) = (b2, a2)
if b2 >= c2:
    (b2, c2) = (c2, b2)
if a1 == a2 and b1 == b2 and c1 == c2:
    print('Boxes are equal')
elif a1 >= a2 and b1 >= b2 and c1 >= c2:
    print('The first box is larger than the second one')
elif a1 <= a2 and b1 <= b2 and c1 <= c2:
    print('The first box is smaller than the second one')
else:
    print('Boxes are incomparable')
