import itertools
d = {}
count = 0
text = open("input.txt", "r")
for lines in text:
    names = lines.split("\n")
    count+=1
    for name in names:
        if name in d:
            d[name] = d[name] + 1
        else:
            d[name] = 1
# баг, 1 место == число переводов на новую строку
#print(d)
fifty = count // 2

for i in sorted(d.items(), key=lambda x: (-x[1], x[0])):
    if i[0] == '':
        continue
    if i[1] > fifty:
        print(i[0])
        break
    else:
        print(i[0])
        print(next(iter(d)))
        break
for key in sorted(d.keys()):
    print(key, d[key])

# if flag == True:
#     print(d.get(format()))