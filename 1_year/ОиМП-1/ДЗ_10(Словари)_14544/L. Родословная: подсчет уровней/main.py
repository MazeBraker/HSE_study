n = int(input())
d = {}
for i in range(n - 1):
    child, parent = input().split()
    if parent not in d:
        d[parent] = None  # имена повторяются, поэтому None только у прародителя
    d[child] = parent

for child, parent in sorted(d.items()):  # sort names in lex order
    level = 0
    print(child, end=' ')
    while child in d:
        # спускаемся по дереву сверху вниз по детям, когда пропустим child, то найдем глубину
        child = d[child]  # опускаемся к корню - потомок становится родителем
        level += 1
    print(level - 1)
