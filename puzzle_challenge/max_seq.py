#!/usr/bin/python2

#A = [[int(i)] for i in raw_input("Gimme a list of nums").split()]
A = [5, 3, 4, 8, 6, 7]


d = len(A) * [1]
lists = len(A) * [[]]
lists[0] = [A[0]]

for i in range(len(A) - 1):
    print "i is: " + str(i + 1)
    lists[i+1] = [A[i+1]]
    for j in range(i + 1):
        print j
        if A[i+1] >= A[j] and d[i+1] <= d[j] + 1:
            d[i+1] = d[j] + 1
            lists[i+1] = lists[j][:] + [A[i+1]]
    print lists[i+1]
    print " "

print max(d)
print max(lists, key=len) 
