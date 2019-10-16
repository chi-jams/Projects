#!/usr/bin/python3

from vpython import *
import random

def gen_rand_vector(low_bound, high_bound):
    return vector(*[random.uniform(low_bound, high_bound) for _ in range(3)])

PLAYBACK_SPEED = 60
disp = canvas(title="I don't understand what's going on here", x=0, y=0,
               width=1280, height=720)
balls = [sphere(pos=gen_rand_vector(-10, 10),
                radius=0.2,
                color=color.white,
                make_trail=True, interval=1, retain=10) for _ in range(100)]
#sun = sphere(pos=vector(0,0,0), radius=2, color=color.red) 

deltat = 1 / PLAYBACK_SPEED
for ball in balls:
    sun_surface_norm = norm(vector(0,0,0) - ball.pos)
    ball.velocity = sun_surface_norm.cross(gen_rand_vector(-20,20))
    #ball.velocity = gen_rand_vector(-20, 20)

while True:
    for ball in balls:
        ball.pos += ball.velocity * deltat
        #a_mag = 400 / mag(sun.pos - ball.pos)**2
        #ball.velocity += deltat * a_mag * (sun.pos - ball.pos)
        for o_ball in balls:
            if ball == o_ball:
                continue
            a_mag = 400 / mag(o_ball.pos - ball.pos)**2
            ball.velocity += 0.05 * deltat * a_mag * (o_ball.pos - ball.pos)

        '''
        dist_to_sun = mag(ball.pos - sun.pos)
        if dist_to_sun < sun.radius + ball.radius:
            sun_surface_norm = norm(sun.pos - ball.pos)
            ball_v_dir = norm(ball.velocity)
            reflect_dir = ball_v_dir - 2 * sun_surface_norm * ball_v_dir.dot(sun_surface_norm)
            ball.velocity = mag(ball.velocity) * 0.01 * reflect_dir
        '''
    rate(PLAYBACK_SPEED)
