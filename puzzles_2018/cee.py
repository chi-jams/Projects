#!/usr/bin/python3

import enchant 

key = "HBSOJGDLUZQRCEYFNIVAPTMWXK"
alp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

msg = """
DAFBE PLJ DU OF BEIPBE
JYRR MJD CBD
CJS DTHNF NDGO K IYMOG
LG IO FOSWF OGM
UQ G GOFRJN OYQL TLQQJS
YHF XQTC GPKT USEUQM
OHY PD MILHC GGRBS
NP VGTGZ BV KZAMAC
AR QWA FTV CTOC XYHUP JVYINGZB
PRS MJD Y XCYU QD HEZ IOYG
YJ QWEUSW QQPRYJG
LIZB QPZM TZG MKRN
"""

rotate = lambda s,i: s[-i % 26:] + s[:-i % 26]


#translate = dict(zip(list(rotate(alp, i)), list(key)))
#for o in range(26):

#o = 12
#o = -1
clock = [12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
#i = 0l
translate = lambda c, i: list(alp)[rotate(key, i).find(c)]
final = ""
d = enchant.Dict("en_US")

for word in msg.split():
    o = 0
    opts = []
    trans = ''.join([translate(c, i + o) if c in key else c for i, c in enumerate(list(word))])
    #while not d.check(trans) and o < 26:
    while o < 26:
        o += 1
        if d.check(trans) or word == "DTHNF" or word == "QWEUSW":
            opts.append((o,trans))
            #opts.append(trans)
        trans = ''.join([translate(c, i + o) if c in key else c for i, c in enumerate(list(word))])

    if d.check(trans) or word == "DTHNF" or word == "QWEUSW":
        opts.append((o,trans))
        #opts.append(trans)
    print(o, opts)

    #final += " " + trans

print(final)
'''
for t, word in enumerate(msg.split()):
    #o = clock[t % len(clock)]
    o = (60 * t + 12) % 24
    blep = ''.join([translate(c, i + o + 1) if c in key else c for i, c in enumerate(list(word))])
    print(o, blep)
    final += ' ' + blep
'''

