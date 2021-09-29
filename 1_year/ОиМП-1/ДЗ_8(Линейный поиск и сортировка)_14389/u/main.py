file = open('input.txt', 'r', encoding='utf8')
parties = {}
votes = False
cnt = 0
file = [line.rstrip() for line in file]
for item in file:
    if item == 'PARTIES:':
        votes = False
    elif item == 'VOTES:':
        votes = True
    elif not votes:
        parties[item] = 0
    else:
        cnt += 1
        for party in parties:
            if item == party:
                parties[party] += 1
p = cnt * 7 / 100
for party in parties:
    if parties[party] >= p:
        print(party)