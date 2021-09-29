#https://github.com/kol060k/Yandex_Algorithm_Training_2021/blob/ae14b598d8c1f79ae9874c2f8730c1aed9a9ab0e/HW8/I.py
children = {}  # словарь, возвращающий детей человека
parent = {}  # словарь, возвращающий родителя человека
n = int(input())
# Заполняем оба словаря:
for i in range(n - 1):
    child_name, parent_name = input().split()
    parent[child_name] = parent_name
    if parent_name not in children:
        children[parent_name] = []
    children[parent_name].append(child_name)

# Найдём прародителя, у него должны быть дети, но при этом не должно быть родителя
TheGodfather = set(children.keys()) - set(parent.keys())
TheGodfather = list(TheGodfather)[0]  # Он всё равно один

# Пройдём по всем людям снизу дерева вверх (от детей к родителям) и с каждым подъёмом будем запоминать
# число всех его потомков. Это алгоритм поиска в ширину с конца.
# Для начала составим очередь от самого старого.
queue = [TheGodfather]
i = 0
while i < len(queue):
    if queue[i] in children:
        queue.extend(children[queue[i]])
    i += 1
# Теперь проходимся по очереди в обратном порядке (идём от детей) и записываем число потомков
descendant_num = {}
for person in reversed(queue):
    descendant_num[person] = 0
    if person in children:
        for child in children[person]:
            descendant_num[person] += descendant_num[child] + 1

# Выводим в лексикографическом порядке
for person in sorted(descendant_num.keys()):
    print(person, descendant_num[person])