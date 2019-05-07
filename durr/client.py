#!/usr/bin/python3

import sys
import requests
import random

if len(sys.argv) != 2:
    print("Usage: {} <N>".format(sys.argv[0]))
    sys.exit(-1)

name = sys.argv[1]
i = 0

while True:
    i += 1
    stuff = {'name': name, 'seeds':
        [random.uniform(0,1.2) for _ in range(1000)]}
    print(stuff)
    r = requests.post("http://localhost:8080/", json=stuff)
