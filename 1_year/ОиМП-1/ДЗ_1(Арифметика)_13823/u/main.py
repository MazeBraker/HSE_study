# h = int(input())
# a = int(input())
# b = int(input())
# print(int(1 + (h - b - 1) / (a - b)))
# h, a, b = map(int, input().split())
# print( (h - a) // (a - b) + 1 )
h, a, b = map(int, input().split())
print((h -b - 1) // (a - b) +  1)
