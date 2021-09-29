file = open('input.txt', 'r', encoding='utf-8')
lines = file.readlines()
class9 = []
class10 = []
class11 = []
for i in lines:
    if int(i.split()[2]) == 9:
        class9.append(i.split()[3])
    elif int(i.split()[2]) == 10:
        class10.append(i.split()[3])
    else:
        class11.append(i.split()[3])
class9 = list(map(int, class9))
class10 = list(map(int, class10))
class11 = list(map(int, class11))
avsum9 = sum(class9) / len(class9)
avsum10 = sum(class10) / len(class10)
avsum11 = sum(class11) / len(class11)
print(avsum9, avsum10, avsum11)
