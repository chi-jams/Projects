#version 410 core

layout( quads, fractional_odd_spacing, ccw ) in;

layout (std140) uniform Matrices {
    mat4 view;
    mat4 projection;
    vec3 viewVector;
};

patch in vec3  tcAmb;
patch in vec3  tcDiff;
patch in vec3  tcSpec;
patch in float tcShiny;
in vec3  tcVertex[];
in vec3  tcNormal[];

out vec3  teAmb;
out vec3  teDiff;
out vec3  teSpec;
out float teShiny;
out vec3  tePosition;
out vec3  teVertex;
out vec3  teNormal;


// I don't even know man, just copypasta'd from the book
void basisFunctions(out float[4] b, out float[4] db, float t) {
    float t1 = (1.0 - t);
    float t12 = t1 * t1;

    // Bernstein polynomials
    b[0] = t12 * t1;
    b[1] = 3.0 * t12 * t;
    b[2] = 3.0 * t1 * t * t;
    b[3] = t * t * t;

    // Derivatives
    db[0] = -3.0 * t1 * t1;
    db[1] = -6.0 * t * t1 + 3.0 * t12;
    db[2] = -3.0 * t * t + 6.0 * t * t1;
    db[3] = 3.0 * t * t;
}


void main() {
    float u = gl_TessCoord.x; // get parameters
    float v = gl_TessCoord.y;

    
    // No way I'm typing all that out, no sir
    vec4 p[16];
    for( int i = 0; i < 16; i++ ) {
        p[i] = gl_in[i].gl_Position;
    }

    // These give you the generic function for bezier interpolation
    float bu[4], bv[4];
    float dbu[4], dbv[4];
    basisFunctions( bu, dbu, u );
    basisFunctions( bv, dbv, v );
    
    // This gives you the actual values from the interpolation
    vec4 outPos = vec4( 0, 0, 0, 0 );   
    vec4 du = vec4( 0, 0, 0, 0 ); 
    vec4 dv = vec4( 0, 0, 0, 0 );
    for( int i = 0; i < 4; i++ ) {
        for( int j = 0; j < 4; j++ ) {

            outPos += p[4*i + j] * bu[i] * bv[j];
            du += p[4*i + j] * dbu[i] * bv[j];
            dv += p[4*i + j] * bu[i] * dbv[j];
        }
    }

    for( int i = 0; i < 16; i++ ) {
        p[i] = vec4( tcVertex[i], 1.0 );
    }
    vec4 outVert = vec4( 0, 0, 0, 0 );   
    for( int i = 0; i < 4; i++ ) {
        for( int j = 0; j < 4; j++ ) {
            outVert += p[4*i + j] * bu[i] * bv[j];
        }
    }

    // output point in Clip Space
    gl_Position = projection * view * outPos;

    teAmb = tcAmb;
    teDiff = tcDiff;
    teSpec = tcSpec;
    teShiny = tcShiny;
    tePosition = outPos.xyz;
    teVertex = outVert.xyz;
    teNormal = normalize( cross( du.xyz, dv.xyz ) );
} 