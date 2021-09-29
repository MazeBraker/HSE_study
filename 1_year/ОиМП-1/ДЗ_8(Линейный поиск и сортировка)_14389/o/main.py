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
max9 = max(class9)
max10 = max(class10)
max11 = max(class11)
print(max9, max10, max11)
