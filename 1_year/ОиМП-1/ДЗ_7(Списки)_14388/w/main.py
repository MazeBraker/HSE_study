nums = list(map(int, input().split()))
len_nums = len(nums)
j = 0  # флаг 0
# за один проход "пузырьком" поднимаем нули в конец списка
# когда 0 нет, то i = j и замена ничего не меняет
for i in range(len_nums):
    if nums[i] != 0:
        nums[j], nums[i] = nums[i], nums[j]
        j += 1
print(*nums)