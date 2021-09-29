words = open("input.txt", "r", encoding="utf8")
a = []
for i in words.read().split():
    a += i.split()
print(len(set(a)))
