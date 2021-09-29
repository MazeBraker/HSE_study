k = int(input())
num = 1
count = 0

while num <= k:
    new = 0
    tmp = num
    while tmp // 10:
        new = (new + tmp % 10) * 10
        tmp //= 10
    new += tmp
    if new == num:
        count += 1
    num += 1
print(count)