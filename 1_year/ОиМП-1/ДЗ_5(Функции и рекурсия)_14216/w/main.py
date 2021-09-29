num = float(input())

def sum_qubs(x, power, step):
    b = int(x ** (1 / power))
    if x - b ** power == 0:
        return str(b ** 3)
    if step == 1:
        return 0
    while sum_qubs(x - b ** power, power, step - 1) == 0:
        b -= 1
        if b <= 0:
            return 0
    return str(b ** 3) + ' ' + sum_qubs(x - b ** power, power, step - 1)


print(sum_qubs(num, 3, 7))