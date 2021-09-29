A = int(input())
B = int(input())
N = int(input())
S = (A * 100 + B) * N
print(S // 100, end=' ')
print(S % 100)