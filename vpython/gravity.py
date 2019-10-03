#!/usr/bin/python3

from vpython import *
import random

balls = [sphere(pos=vector(*[random.uniform(-10, 10) for _ in range(3)]),
                radius=0.5,
                color=color.cyan) for _ in range(100)]
sun = sphere(pos=vector(0,0,0), radius=2, color=color.red) 

deltat = 0.005
t = 0
for ball in balls:
    ball.velocity = vector(*[random.uniform(-1, 1) for _ in range(3)])

while True:
    for ball in balls:
        ball.pos += ball.velocity * deltat
        ball.velocity += 0.00001 * (sun.pos - ball.pos)
