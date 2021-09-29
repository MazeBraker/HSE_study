infile = open('input.txt', 'r', encoding='utf8')
tmp = [[0, i] for i in range(102)]
res = []

for line in infile:
    tmp[int(line.split()[-2])][0] += 1
max_ = max(tmp)[0]

for i in range(102):
    if tmp[i][0] == max_:
        res.append(tmp[i][1])
infile.close()

print(*res)