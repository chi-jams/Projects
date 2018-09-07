#!/usr/bin/python3

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


for i in range(26):
    translate = dict(zip(list(rotate(alp, i)), list(key)))
    print(translate)
    dec = ''.join([translate[i] if i in translate else i for i in list(msg)])
    print(dec)
