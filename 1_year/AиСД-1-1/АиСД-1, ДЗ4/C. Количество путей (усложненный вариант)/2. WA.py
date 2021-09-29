N = int(input())
result_of_chisel = [1]

while N != 1:
    result_of_chisel.append(N)
    if N % 3 == 0:
        N = N // 3
    elif N % 2 == 0:
        N = N // 2
    else:
        N = N - 1
result_of_chisel.sort()

print(len(result_of_chisel) - 1)
print(*(result_of_chisel))

