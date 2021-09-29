n = int(input())
nums = set(range(1, n + 1))
while True:
    guess = input()
    if guess == 'HELP':
        break
    guess = set(map(int, guess.split()))
    ans = input()
    if ans == 'YES':
        nums &= guess
    else:
        nums -= guess

print(*sorted(nums))
