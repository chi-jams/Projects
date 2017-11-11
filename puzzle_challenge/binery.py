#!/usr/bin/python2

n = input()

def fibk(pat_len, p):
    nums = [1]
    for i in range(pat_len - 1):
        nums.append(sum(nums))

    for i in range(p - pat_len):
        nums.append(sum(nums[-pat_len:]) % (int(1e9) + 7))
    return nums[-1]

for i in range(n):
    num_size, pattern = raw_input().split()
    num_size = int(num_size)
            
    print fibk(len(pattern), num_size + 2) 
