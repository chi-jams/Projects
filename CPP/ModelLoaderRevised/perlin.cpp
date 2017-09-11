
#include "perlin.h"
#include <cmath>

#include <iostream>

#include <GL/glew.h>

GLuint genTexture( int texWidth, int texHeight ) {

    // Set the base frequency
    // SetFrequency( 4.0 );

    GLubyte *texData = new GLubyte[ texWidth * texHeight * 4 ];

    double xRange = 1.0;
    double yRange = 1.0;

    double xFactor = xRange / texWidth;
    double yFactor = yRange / texHeight;

    for( int oct = 0; oct < 4; oct++ ) {
        // Set the current octave
        // SetOctaveCount( oct + 1 )
        for( int u = 0; u < texWidth; u++ ) {
            for( int v = 0; v < texHeight; v++ ) {
                double x = xFactor * u;
                double y = yFactor * v;
                double z = 0.0;

                float val = perlin( x, y, z );

                val = ( val * 1.0f ) * 0.5f;

                if( val > 1.0 )
                    val = 1.0;
                else if( val < 0.0 )
                    val = 0.0;

                // Alright, so here's how the data's layed out:
                // at each "pixel," the x,y,z,w values are each a value
                // in the octaves in ascending order
                // then we have items on the same row adjacent to each other
                // The data is populated by column
                texData[ ( ( v * texWidth + u ) * 4 ) + oct ] = (GLubyte) ( val * 255.0f );
            }
        }
    }


    GLuint texID;
    glGenTextures( 1, &texID );
    glBindTexture( GL_TEXTURE_2D, texID );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
                      texWidth, texHeight, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, texData );

        glGenerateMipmap( GL_TEXTURE_2D );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
        
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );


    glBindTexture( GL_TEXTURE_2D, 0 );

    delete [] texData;

    return texID;
}

// Private, internal functions
double fade( double t );
double lerp( double t, double a, double b );
double grad( int hash, double x, double y, double z );

// This is a bunch of random numbers that Perlin decided
// were THE random numbers.
// There's only 256 of them, but they're duplicated because
// reasons, and there's a for loop writing into a const array
// in the tutorials, but I'm lazy and don't know if you can do 
// that in C++
const int p[512] = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,
    140,36,103,30,69,142,8,99,37,240,21,10,23,190, 6,148,247,
    120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,
    33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,
    71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,
    133,230,220,105,92,41,55,46,245,40,244,102,143,54, 65,25,
    63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,
    226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,
    59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,
    2,44,154,163, 70,221,153,101,155,167, 43,172,9,129,22,39,253,
    19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,
    249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,
    115,121,50,45,127, 4,150,254,138,236,205,93,222,114,67,29,24,
    72,243,141,128,195,78,66,215,61,156,180,
    // ... it's a lot of numbers
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,
    140,36,103,30,69,142,8,99,37,240,21,10,23,190, 6,148,247,
    120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,
    33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,
    71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,
    133,230,220,105,92,41,55,46,245,40,244,102,143,54, 65,25,
    63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,
    226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,
    59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,
    2,44,154,163, 70,221,153,101,155,167, 43,172,9,129,22,39,253,
    19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,
    249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,
    115,121,50,45,127, 4,150,254,138,236,205,93,222,114,67,29,24,
    72,243,141,128,195,78,66,215,61,156,180
};

double perlin( double x, double y, double z ) {

    // Find the unit cube that contains the point
    // Also hash it into (0, 255)
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;

    //std::cout << "Unit cube: ( " << X << ", " << Y << ", " << Z << " )" << std::endl;

    // Find the location in the unit cube
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    //std::cout << "Location in cube: ( " << x << ", " << y << ", " << z << " )" << std::endl;

    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    //std::cout << "Fade values: ( " << u << ", " << v << ", " << w << " )" << std::endl;

    // Dude I don't even know at this point
    int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,
        B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;

    // What is this unreal level of interpolation
    return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),
                                   grad(p[BA  ], x-1, y  , z   )),
                           lerp(u, grad(p[AB  ], x  , y-1, z   ),
                                   grad(p[BB  ], x-1, y-1, z   ))),
                   lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),
                                   grad(p[BA+1], x-1, y  , z-1 )),
                           lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
                                   grad(p[BB+1], x-1, y-1, z-1 ))));
}

// This is the function that makes sure that the diagonal isn't just
// straigh, otherwise it'll look unnatural
double fade( double t ) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp( double t, double a, double b ) {
    return a + t * (b - a); 
}

double grad( int hash, double x, double y, double z ) {

    // Convert the low 4 bits (0-15) into 12 gradient
    // directions
    int h = hash & 15;

    double u = y;
    if( h < 8 )
        u = x;

    double v = z;
    if( h < 4 )
        v = y;
    else if( h == 12 || h == 14 )
        v = x;

    double gradient = -u;
    if( h % 2 == 0 )
        gradient = u;

    if( h % 3 == 0 )
        gradient += v;
    else
        gradient -= v;

    return gradient;
}