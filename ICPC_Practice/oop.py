N, Q = [int(i) for i in input().split(" ")]

words = []
for i in range(N):
    words.append(input())

for i in range(Q):
    pattern = input().split('*')
    len0, len1 = len(pattern[0]), len(pattern[1])
    match = 0
    for word in words:
        if len0 + len1 > len(word):
            continue

        if pattern[0] == word[:len0] and (len1 == 0 or pattern[1] == word[-len1:]):
            match += 1
    print(match)
