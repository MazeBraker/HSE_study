from _operator import xor
from functools import reduce
print(*reduce(lambda x, y: map(xor, x, y), map(lambda line: map(int, line.split()), map(lambda _: input(), range(int(input()))))))