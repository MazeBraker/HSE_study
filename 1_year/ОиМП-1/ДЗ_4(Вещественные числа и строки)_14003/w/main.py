stroke = input()
probel = ''
i = 0
while i < len(stroke):
    if i != len(stroke) - 1:
        probel = probel + stroke[i] + '*'
        i += 1
    else:
        probel += stroke[i]
        i += 1
print(probel)
