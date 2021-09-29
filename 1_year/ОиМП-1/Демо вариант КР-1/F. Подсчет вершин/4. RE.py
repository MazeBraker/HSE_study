s = input()
one = s.find('h')
last = s.rfind('h')
print(s[:one + 1] + s[last:one + 1:-1] + s[last:])
