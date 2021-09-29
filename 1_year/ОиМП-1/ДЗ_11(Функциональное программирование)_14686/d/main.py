from itertools import repeat
print(0 in list(map(lambda r: int(r()), repeat(input, int(input())))))

# import sys
# from itertools import islice
#
# print(any(x == 0 for x in map(int, islice(sys.stdin, int(next(sys.stdin))))))
