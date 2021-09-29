s = input()
if s.find('f') != -1:
    if s.rfind('f') > s.find('f'):
        one = s.find('f')
        two1 = s.replace(s[one], 'g', 1)
        two = two1.rfind('f')
        print(one, two)
    elif s.find('f') == s.rfind('f'):
        print(s.find('f'))
