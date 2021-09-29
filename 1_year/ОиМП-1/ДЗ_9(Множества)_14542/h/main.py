n = int(input())
all_nums = set(range(1, n + 1))
possible_nums = all_nums
while True:
    guess = input()
    if guess == 'HELP':
        break
    guess = {int(x) for x in guess.split()}
    if len(possible_nums & guess) > len(possible_nums) / 2:
        print('YES')
        possible_nums &= guess
    else:
        print('NO')
        possible_nums &= all_nums - guess

print(' '.join([str(x) for x in sorted(possible_nums)]))