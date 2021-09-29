s = input()
k = ''
for i in range(len(s)):
    if i % 3 != 0:
        k = k + s[i]
print(k)
