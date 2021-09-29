infile = open('input.txt', 'r', encoding='utf8')
outfile = open('output.txt', 'w', encoding='utf8')
names = []
for i in infile:
    tmp = i.split()
    names.append((tmp[0], tmp[1], tmp[3]))
names.sort()

for i in names:
    print(*i, file=outfile)

outfile.close()
infile.close()