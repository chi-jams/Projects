#version 410 core

in vec3 gAmb;
in vec3 gDiff;
in vec3 gSpec;
in vec3 gPosition;
in vec3 gVertex;
in vec3 gNormal;
in float gShiny;

in vec3 triHeights;

out vec4 fColor;

layout (std140) uniform Matrices {
    mat4 view;
    mat4 projection;
    vec3 viewVector;
};

// Make a point light
layout (std140) uniform Light {
    vec3 lightPos;
    vec3 lightA;
    vec3 lightD;
    vec3 lightS;
    float shininess;
};

/* All the code below was pretty much copy-pasta'd off of Ken Perlin's website
   on the perlin noise function. A couple of minor changes were made in order
   to make the functions work at an appropriate framerate, namely the lerp was
   changed to the built in mix function
*/

// This is a bunch of random numbers that Perlin decided
// were THE random numbers.
// There's only 256 of them, but they're duplicated because
// reasons, and there's a for loop writing into a const array
// in the tutorials, but I'm lazy and don't know if you can do 
// that in C++
uniform int p[512] = {
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

// This is the function that makes sure that the diagonal isn't just
// straigh, otherwise it'll look unnatural
float fade( float t ) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float grad( int hash, float x, float y, float z ) {

    // Convert the low 4 bits (0-15) into 12 gradient
    // directions
    int h = hash & 15;

    float u = y;
    if( h < 8 )
        u = x;

    float v = z;
    if( h < 4 )
        v = y;
    else if( h == 12 || h == 14 )
        v = x;

    float gradient = -u;
    if( h % 2 == 0 )
        gradient = u;

    if( h % 3 == 0 )
        gradient += v;
    else
        gradient -= v;

    return gradient;
}

float perlin( float x, float y, float z ) {

    // Find the unit cube that contains the point
    // Also hash it into (0, 255)
    int X = int(floor(x)) & 255;
    int Y = int(floor(y)) & 255;
    int Z = int(floor(z)) & 255;

    //std::cout << "Unit cube: ( " << X << ", " << Y << ", " << Z << " )" << std::endl;

    // Find the location in the unit cube
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    //std::cout << "Location in cube: ( " << x << ", " << y << ", " << z << " )" << std::endl;

    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    //std::cout << "Fade values: ( " << u << ", " << v << ", " << w << " )" << std::endl;

    // Dude I don't even know at this point
    int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,
        B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;

    // What is this unreal level of interpolation
    return mix( mix( mix( grad(p[AA  ], x  , y  , z   ),
                          grad(p[BA  ], x-1, y  , z   ), u),
                     mix( grad(p[AB  ], x  , y-1, z   ),
                          grad(p[BB  ], x-1, y-1, z   ), u), v),
                mix( mix( grad(p[AA+1], x  , y  , z-1 ),
                          grad(p[BA+1], x-1, y  , z-1 ), u),
                     mix( grad(p[AB+1], x  , y-1, z-1 ),
                          grad(p[BB+1], x-1, y-1, z-1 ), u), v), w) + 0.5;
}

float octavePerlin( float x, float y, float z, int octaves, float persistence ) {
    float total = 0;
    float frequency = 1;
    float amplitude = 1;
    float maxValue = 0; 
    for( int i=0; i<octaves; i++ ) {
        total += perlin(x * frequency, y * frequency, z * frequency) * amplitude;
        
        maxValue += amplitude;
        
        amplitude *= persistence;
        frequency *= 2;
    }
    
    return total/maxValue;
}

float perlin( vec3 seed ) {
    return perlin( seed.x, seed.y, seed.z );
}

float octavePerlin( vec3 seed, int octaves, float persistence ) {
    return octavePerlin( seed.x, seed.y, seed.z, octaves, persistence );
}

void main()
{
    vec3 lightDir = normalize( lightPos - gPosition );
    vec3 n = normalize( gNormal );

    vec3 view = viewVector;
    
    float x = gVertex.x;
    float y = gVertex.y;
    float z = gVertex.z;
    float t = 0.5 + sin( 10 * ( x + z ) + 10 * ( octavePerlin( gPosition * 5, 5, 0.5 ) ) ) ;

    vec3 gDiffInv = vec3( 1.0 - gDiff.x, 1.0 - gDiff.y, 1.0 - gDiff.z );
    vec3 diffuse = lightD * gDiff * max( dot( lightDir, gNormal ), 0.0 );
    vec3 diffInv = lightD * gDiffInv * max( dot( lightDir, gNormal ), 0.0 );
    vec3 diffOut = mix( diffuse, diffInv, t );

    vec3 halfway = normalize( lightDir + viewVector );
    vec3 specular = lightS * gSpec * pow( max( dot( halfway, n ), 0.0 ), gShiny );

    vec3 ambient = gAmb * lightA;
    
    fColor = vec4( ambient + diffOut + specular, 1.0 ); 
} 