s = input()
one = s.find('h')
last = s.rfind('h')
print(s[:one + 1] + s[last - 1:one:-1] + s[last:])
