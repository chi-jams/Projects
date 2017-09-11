
#ifndef _PERLIN_H
#define _PERLIN_H

#include <GL/glew.h>

GLuint genTexture( int texWidth, int texHeight );
double perlin( double x, double y, double z );

#endif