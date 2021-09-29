s = input()
one = s.find('h')
last = s.rfind('h')
print(s[:one + 1] + s[one + 1:last] * 2 + s[last:])
