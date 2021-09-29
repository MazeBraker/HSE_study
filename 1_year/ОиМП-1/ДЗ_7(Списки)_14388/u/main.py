N, K = [int(i) for i in input().split()]

a_list = ['I' for i in range(N)]

for i in range(K):
    l, r = [int(i) for i in input().split()]
    for j in range(l - 1, r):
        if a_list[j] != '.':
            a_list[j] = '.'

print(''.join(a_list))