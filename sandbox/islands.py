#!/bin/python3

import random
import sys

def print_arr(arr):
    for row in arr:
        print(''.join(chr(9617) if i == 0 else chr(9608) for i in row))

def find_island(arr, i, j, consumed):
    # If the row or col is out of bounds
    if i < 0 or i >= len(arr) or j < 0 or j >= len(arr[0]):
        return consumed
    if arr[i][j] != 1 or (i, j) in consumed:
        return consumed

    consumed.append((i, j))
    consumed = find_island(arr, i + 1, j, consumed)
    consumed = find_island(arr, i - 1, j, consumed)
    consumed = find_island(arr, i, j + 1, consumed)
    consumed = find_island(arr, i, j - 1, consumed)

    return consumed

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

for i, row in enumerate(arr):
    for j, col in enumerate(row):
        if col == 1 and (i, j) not in consumed:
            islands += 1
            consumed = find_island(arr, i, j, consumed)

print(islands)
