d = dict()
while True:
    try:
        man, counter = input().split()
        if man == counter == 0:
            break
        counter = int(counter)
        d[man] = d.get(man, 0) + counter
    except:
        break

for key in sorted(d.keys()):
    print(key, d[key])