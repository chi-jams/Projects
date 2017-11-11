#!/usr/bin/python2

h = [5,4,3,2,1]
bl = [1,5,10,15,20]
wl = [4,9,14,20,25]

fl = zip(h,bl,wl)

print fl
fl.sort(cmp=lambda x,y: 1 if (x[0] > y[0] and x[2] >= y[1] and x[1] >= y[2]) or (x[0] < y[0] and not (x[2] >= y[1] and x[1] >= y[2])) else -1)

print fl
