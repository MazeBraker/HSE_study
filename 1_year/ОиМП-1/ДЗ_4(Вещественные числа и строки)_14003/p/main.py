s = input()
if s.find('f') != -1:
    if s.find('f') == s.rfind('f'):
        print(-1)
    else:
        one = s.find('f')
        two = s.replace(s[one], '0', 1)
        print(two.find('f'))
else:
    print(-2)
