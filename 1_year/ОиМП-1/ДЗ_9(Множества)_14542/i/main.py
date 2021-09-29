std_cnt = int(input())
all_know = []
one_know = []
one_know_lang = set()

for i in range(std_cnt):
    all_lang = int(input())
    temp_list = set()
    for j in range(all_lang):
        temp = str(input())
        temp_mas = []
        temp_mas.append(temp)
        temp_list.update(temp_mas)

        if temp not in all_know:
            all_know.append(temp)

    if i == 0:
        one_know_lang.update(temp_list)
    else:
        one_know_lang = one_know_lang & temp_list

all_know.sort()
one_know = []
for i in one_know_lang:
    one_know.append(str(i))
one_know.sort()

print(len(one_know))
print('\n'.join([str(i) for i in one_know]))
print(len(all_know))
print('\n'.join([str(i) for i in all_know]))
