inFile = open('input.txt', 'r', encoding='utf8')
scores = []
passing_score = 0
K = int(inFile.readline())
for line in inFile:
    if min(tuple(map(int, line.split()[-3:]))) > 39:
        scores.append(sum(tuple(map(int, line.split()[-3:]))))
scores.sort(reverse=True)

if len(scores) > K:
    if scores[0] == scores[K]:
        passing_score = 1
    elif scores[K - 1] > scores[K]:
        passing_score = scores[K - 1]
    elif scores[K - 1] == scores[K]:
        for s in range(K - 1, 0, -1):
            if scores[s - 1] - scores[s]:
                passing_score = scores[s - 1]
                break
print(passing_score)
inFile.close()