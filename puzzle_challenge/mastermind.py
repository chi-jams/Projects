
from itertools import product

def match_first(colors):
    first = ('WBWY', 1, 1)

    pos = 0    
    for i in range(0,4):
        if colors[i] == first[i]:
            pos += 1
        if pos > 1:
            return False

        

second = ('YRWR', 1, 1)
third = ('WRBB', 2, 1)

for colors in product('RWBY', 'RWBY', 'RWBY', 'RWBY'):
    

