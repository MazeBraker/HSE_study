def moveTower(height, from_p, to_p, other_p):
    if height < 1:
        return
    moveTower(height - 1, from_p, other_p, to_p)
    moveDisk(height, from_p, to_p)
    moveTower(height - 1, other_p, to_p, from_p)


def moveDisk(h, fp, tp):
    print(h, fp, tp)


# n = int(input())
# moveTower(n, "1", "3", "2")
#
# def move(n, x, y):
#     if n == 1:
#         print(n, x, y)
#     else:
#         tmp = 6 - x - y
#         move(n - 1, x, tmp)
#         print(n, x, y)
#         move(n - 1, tmp, y)
#
#
# disks = int(input())
# move(disks, 1, 3)