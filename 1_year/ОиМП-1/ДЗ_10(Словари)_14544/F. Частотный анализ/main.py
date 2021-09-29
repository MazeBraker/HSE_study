d = {}
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

for i in sorted(d.items(), key=lambda x: (-x[1], x[0])):
    print(i[0])

# d = dict()
# text = open("input.txt", "r")
# for line in text:
#     line = line.strip()
#     # line = line.lower()
#     words = line.split(" ")
#     for word in words:
#         if word in d:
#             d[word] = d[word] + 1
#         else:
#             d[word] = 1
#
# dictlist = []
# for key, value in d.items():
#     temp = [key,value]
#     dictlist.append(temp)
# dictlist.sort(key=lambda x: x[1], reverse=True)
# for key in dictlist:
#     print(key[0])