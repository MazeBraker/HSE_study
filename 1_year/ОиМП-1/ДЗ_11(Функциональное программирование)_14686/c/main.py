print(min(filter(lambda x: x % 2 == 1, map(int, input().split()))))
# print(min(map(int, input().split()), key=lambda x: (not x % 2, x)))