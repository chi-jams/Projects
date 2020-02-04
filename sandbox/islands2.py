#!/bin/python3

import random
import sys

# An implementation but this time I'm not dumb

def print_arr(arr):
    for row in arr:
        print(''.join(chr(9617) if i == 0 else chr(9608) for i in row))

if len(sys.argv) != 2:
    print("Usage: {} <n>".format(sys.argv[0]))
    sys.exit(-1)

try:
    n = int(sys.argv[1])
    if n < 1:
        raise ValueError
except ValueError:
    print("n must be a positive int!")
    sys.exit(-1)

random.seed()

arr = [[random.randint(0,1) for _ in range(n)] for _ in range(n)]

consumed = []

islands = 0

print_arr(arr)


