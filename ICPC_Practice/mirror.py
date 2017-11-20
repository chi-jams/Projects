
n = eval(input())

for i in range(n):
    row, col = input().split(' ')
    img = []
    for j in range(eval(row)):
        img.append(input()[::-1])

    print('Test ' + str(i+1))
    for j in reversed(img):
        print(j)



