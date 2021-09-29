n = int(input())
if 10 < n < 20 or 4 < (n % 10) < 10 or n % 10 == 0:
    print(n, 'korov')
elif n % 10 == 1:
    print(n, 'korova')
else:
    print(n, 'korovy')
