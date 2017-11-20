import re

nums = [["xxxxx",
"x...x",
"x...x",
"x...x",
"x...x",
"x...x",
"xxxxx"],

["....x",
"....x",
"....x",
"....x",
"....x",
"....x",
"....x"],

["xxxxx",
"....x",
"....x",
"xxxxx",
"x....",
"x....",
"xxxxx"],

["xxxxx",
"....x",
"....x",
"xxxxx",
"....x",
"....x",
"xxxxx"],

["x...x",
"x...x",
"x...x",
"xxxxx",
"....x",
"....x",
"....x"],

["xxxxx",
"x....",
"x....",
"xxxxx",
"....x",
"....x",
"xxxxx"],

["xxxxx",
"x....",
"x....",
"xxxxx",
"x...x",
"x...x",
"xxxxx"],

["xxxxx",
"....x",
"....x",
"....x",
"....x",
"....x",
"....x"],

["xxxxx",
"x...x",
"x...x",
"xxxxx",
"x...x",
"x...x",
"xxxxx"],

["xxxxx",
"x...x",
"x...x",
"xxxxx",
"....x",
"....x",
"xxxxx"],

[".....",
"..x..",
"..x..",
"xxxxx",
"..x..",
"..x..",
"....."]]

lines = []

for i in range(7):
    lines.append([digit[:-1] if len(digit) == 6 else digit for digit in re.findall('.{5}.?', input())])

digits = [[] for i in range(len(lines[0]))];

for row in lines:
    for i, digit in enumerate(row):
        digits[i].append(digit)

eqn = ""
for digit in digits:
    eqn += str(nums.index(digit)) if nums.index(digit) != 10 else '+'

num = []
for digit in str(eval(eqn)):
    num += [nums[int(digit)]]

output = [[] for i in range(7)]
for digit in num:
    for i, seg in enumerate(digit):
        output[i] += seg + '.'

for line in output:
    print("".join(line[:-1]))