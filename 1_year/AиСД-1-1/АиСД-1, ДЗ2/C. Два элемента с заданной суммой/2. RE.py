N, S = list(map(int, input().split()))
lst = [int(i) for i in input().split()]
left = 0
right = N - 1
flazhochik = True
while left != right:
    cursum = lst[left] + lst[right]
    if cursum < S:
        left += 1
    elif cursum > S:
        right -= 1
    else:
        print("YES")
        flazhochik = False
        break
if flazhochik:
    print("NO")
