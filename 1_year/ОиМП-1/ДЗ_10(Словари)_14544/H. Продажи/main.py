d = {}
while True:
    try:
        string = input()
        #param содержит turple название вещи и кол-во
        name, *param = string.split()
        if name in d:
            d[name].append(param)
        else:
            d[name] = [param]  # создаем лист кортежей [['paper', '5'], ['paper', '10']]
    except ValueError:
        #print ("Error: EOF or empty input!")
        string == ""
        break

for name, param in sorted(d.items()):
    print(name + ":")
    stats = {}
    for val in param:
        # суммируем кол-во одинаковых предметов
        # val[0] - название прдмета в словаре, stats.get(val[0], 0) - кол-во, int(val[1]) - кол-во текущего предмета
        stats[val[0]] = stats.get(val[0], 0) + int(val[1])
        print(stats[val[0]])
    # for name in sorted(stats.keys()):
    #     print(name, end=" ")  # name of thing
    #     print(stats[name])  # кол-во