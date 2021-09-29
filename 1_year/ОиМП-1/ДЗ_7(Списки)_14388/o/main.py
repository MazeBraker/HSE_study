def reflect_inplace(arr, i, j):
    for k in range(0, (j - i) // 2):
        arr[i + k], arr[j - k - 1] = arr[j - k - 1], arr[i + k]


def cyclic_shift(arr, offset):
    reflect_inplace(arr, 0, offset)
    reflect_inplace(arr, offset, len(arr))
    reflect_inplace(arr, 0, len(arr))


a = input().split()
cyclic_shift(a, -1)
print(*a)
