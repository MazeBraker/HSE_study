a = int(input())
b = int(input())
c = b - a + 1  # количество квартир
if b % c == 0:  # проверка на последнию кв
    print('YES')
else:
    print('NO')