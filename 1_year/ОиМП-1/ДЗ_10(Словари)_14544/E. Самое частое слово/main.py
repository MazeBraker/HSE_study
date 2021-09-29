d = dict()
text = open("input.txt", "r")
for line in text:
    line = line.strip()
    # line = line.lower()
    words = line.split(" ")
    for word in words:
        if word in d:
            d[word] = d[word] + 1
        else:
            d[word] = 1
max_count = max(sorted(d), key=d.get)
print(max_count)
# for key in sorted(list(d.keys())):
#     print(key, ":", d[key])