a = list(map(int, input().split()))
Petya = int(input())
position = 0
while position < len(a) and a[position] >= Petya:
    position += 1
print(position + 1)
