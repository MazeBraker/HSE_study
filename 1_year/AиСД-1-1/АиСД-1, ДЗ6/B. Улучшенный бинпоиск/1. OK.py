scientists = int(input())
hours = [[int(j) for j in input().split()] for i in range(scientists)]  # нарезаем на кортежи
hours = sorted(hours, key=lambda x: x[-2])  # сортируем по левому концу - по приходу в лабу
k = 0  # счетчик
n = len(hours)
for i in range(n - 1):
    if hours[i + 1][0] > hours[i][1]:  # сверяем начало и конец 1го и 2го ученных
        print(hours[i][0], hours[i][1])  # если больше,то пересечений нет, и все ок
        k += 1  # счетчит показываем у скольких отрезков нет пересечений, то есть различных временных множеств
    else:
        k = 0
        hours[i + 1][0] = hours[i][0]  # если пересечение есть, то мы как бы слепливаем их в один интервал
        hours[i + 1][1] = max(hours[i][1], hours[i + 1][1])
print(hours[n - 1][0], hours[n - 1][1])
# [i][j]: i - номер ученого(с 0), j - 0 или 1(начало или конец)
