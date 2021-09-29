s = input()
one = s.find('h')
last = s.rfind('h')
print(s.replace(s[one + 1:last], s[last - 1:one:-1]))
