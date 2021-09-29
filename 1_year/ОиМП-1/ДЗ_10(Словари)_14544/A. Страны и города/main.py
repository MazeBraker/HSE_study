countryofcity = {}
for now in range(int(input())):
    country, *cities = input().split()
    for city in cities:
        countryofcity[city] = country

for now in range(int(input())):
    print(countryofcity[input()])
