n = int(input())
List = list(map(int, input().split()))
a = int(input())
k = abs(a - List[0])
j = List[0]
for i in range(len(List)):
    if abs(a - List[i]) < k:
        k = abs(a - List[i])
        j = List[i]
print(j)
