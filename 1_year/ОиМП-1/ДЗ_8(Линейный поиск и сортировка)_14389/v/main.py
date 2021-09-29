file = open('input.txt', 'r', encoding='utf8')
file = [line.rstrip() for line in file]  # read a file line-by-line into a list
parties = {}
votes = False
# print(file)
for item in file:
    if item == 'PARTIES:':
        votes = False
    elif item == 'VOTES:':
        votes = True
    elif not votes:
        parties[item] = 0
    else:
        for party in parties:
            if item == party:
                parties[party] += 1
out = []
for party in parties:
    out.append({'party': party, 'n': int(parties[party])})

out = sorted(out, key=lambda i: (-i['n'], i['party']))
for i in range(len(out)):
    print(out[i]['party'])