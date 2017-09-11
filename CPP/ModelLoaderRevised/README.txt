Daichi Jameson -- Layth (Lives on!)
Homework 3 -- Procedural Noise Textures

Description:

This program procedurally generates a texture onto a tessellated teapot.
It displays the scene using a blinn-phong lighting algorithm.
A light moves around in a circle dynamically to get lighting from different angles.
The user may also view the wireframs of the teapot and the flooring if they so desire.

Usage:

The user may control the arcball camera by clicking and dragging the on the screen.
The user may additionally zoom in and out by scrolling up and down.

The point around which the light revolves may be moved around by pressing the w, a, s, d, space, and left control keys.

The user may increase and decrease the tessellation levels by pressing the '-' and '=' keys respectively. This actually changes the look of the texture, kind of like how chiseling out different slices of rock changes the look of the rock. It's hard to explain in text, but it's kind of neat, and worth checking out.

If the user would like to quit, they may press ESC or q.

Compilation:

The user should be able to just go to the console and type 'gmake'

If this does not work, the user may need to change the opengl include directory to their respective machine's opengl directories.

You may also need to put your won glew32.dll in there, but I'm not sure if it's completely necessary.

Notes:

I ended up switching from putting a perlin noise funtion on a texture and then applying it to a model to just generating the perlin noise in the fragment shader. It made the whole process significantly easier. 

I am also not sure what number of octaves, persistence, wood/marble, and colors are appropriate, but I feel like my teapot looks pretty marbly. 

How long did this assignment take you?

Not too long! There was a lot of time spent on trying to get textures to work, even though I threw that out in the end. The procedural texture part didn't actually take too long and only took a couple of hours. It was probably around 3-4 total, definitely a good amount.

How fun was this assignment?

9,
This assignment was certainly really cool. I stuck myself into a time crunch becaus I is smart, but it was still a lot of fun trying to get the teapot to look good by tuning the noise functions.
