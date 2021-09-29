def quadro(i):
    num = int(input())
    if num == 0 and i == 0:
        return print(0)
    elif num == 0:
        return
    if num % (num ** 0.5) == 0:
        i += 1
        quadro(i)
        return print(num, end=' ')
    quadro(i)


quadro(0)