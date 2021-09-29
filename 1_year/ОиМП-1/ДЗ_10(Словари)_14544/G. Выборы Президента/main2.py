inFile = open('input.txt', 'r', encoding='utf8')
outFile = open('output.txt', 'w', encoding='utf8')

text = inFile.readlines()
names_stack = []
# Добавили всех подряд как в стэк
for strings in text:
    name = strings.strip()
    if name == "":
        continue
    names_stack.append(name)

all_cnt = len(names_stack)
cands_dict = {}
# Подсчитали
for cands in names_stack:
    cands_dict[cands] = cands_dict.get(cands, 0) + 1
# меняем имя и кол-во местами  ## превращаем dict в list для удобной сортировки
# cands_dict = dict((name, cnt) for cnt,name in cands_dict.items())
cands_dict = [(name, cnt) for cnt, name in cands_dict.items()]

cands_dict.sort(key=lambda x: x[0], reverse=True)

if cands_dict[0][0] > (all_cnt // 2):
    print(cands_dict[0][1], file=outFile)
else:
    print(cands_dict[0][1], cands_dict[1][1], sep="\n", file=outFile)
inFile.close()
outFile.close()
