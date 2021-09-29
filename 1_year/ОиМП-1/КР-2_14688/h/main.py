def vasya_pos(ch_numb, res):
    max_result = max(res)
    max_position = res.index(max_result)
    if ((ch_numb - 1) - max_position) < 2:
        return 0
    Vasya_position = max_position+1
    Vasya_result = res[Vasya_position]
    if (Vasya_result % 10) != 5 or res[Vasya_position + 1] > Vasya_result:
        return 0
    if Vasya_result == max_result:
        Vasya_position = max_position
    return Vasya_position+1


with open('input.txt') as file:
    lines = file.readlines()
    champions_number = int(lines[0])
    results = list(map(int, lines[1].split()))

with open('output.txt', 'w') as file:
    file.write(str(vasya_pos(champions_number, results)))