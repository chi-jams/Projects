#!/usr/bin/python3

from vpython import *
import random

PLAYBACK_SPEED = 60
disp = canvas(title="I don't understand what's going on here", x=0, y=0,
               width=1280, height=720)
balls = [sphere(pos=vector(*[random.uniform(-10, 10) for _ in range(3)]),
                radius=0.5,
                color=color.cyan) for _ in range(10)]
sun = sphere(pos=vector(0,0,0), radius=2, color=color.red) 

deltat = 1 / PLAYBACK_SPEED
for ball in balls:
    sun_surface_norm = norm(sun.pos - ball.pos)
    ball.velocity = sun_surface_norm.cross(vector(*[random.uniform(-10, 10) for _ in range(3)]))

while True:
    for ball in balls:
        ball.pos += ball.velocity * deltat
        a_mag = 100 / mag(sun.pos - ball.pos)**2
        ball.velocity += deltat * a_mag * (sun.pos - ball.pos)

        dist_to_sun = mag(ball.pos - sun.pos)
        if dist_to_sun < sun.radius + ball.radius:
            sun_surface_norm = norm(sun.pos - ball.pos)
            ball_v_dir = norm(ball.velocity)
            reflect_dir = ball_v_dir - 2 * sun_surface_norm * ball_v_dir.dot(sun_surface_norm)
            ball.velocity = mag(ball.velocity) * reflect_dir
    rate(PLAYBACK_SPEED)
