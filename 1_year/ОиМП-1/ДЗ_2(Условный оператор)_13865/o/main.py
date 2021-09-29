a = int(input())
b = int(input())
c = int(input())
if a + b <= c or a + c <= b or b + c <= a or a + b + c <= 0:
    print('impossible')
else:
    if a ** 2 == b ** 2 + c ** 2 or b ** 2 == a ** 2 + c ** 2\
            or c ** 2 == b ** 2 + a ** 2:
        print('rectangular')
    elif (a * a > b * b + c * c) or (b * b > a * a + c * c) \
            or (c * c > a * a + b * b):
        print('obtuse')
    else:
        print('acute')
