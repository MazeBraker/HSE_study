myset1 = set(map(int, input().split()))
myset2 = set(map(int, input().split()))
print(*sorted((myset1 & myset2)))
