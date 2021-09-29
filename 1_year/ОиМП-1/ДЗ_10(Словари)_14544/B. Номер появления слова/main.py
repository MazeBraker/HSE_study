from collections import Counter

counter = Counter()
with open('input.txt') as file:
    for line in file:
        for word in line.strip().split():
            print(counter[word], end=' ')
            counter[word] += 1
