
#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vAmb[];
in vec3 vDiff[];
in vec3 vSpec[];
in float vShiny[];
in vec3 vPosition[];
in vec3 vNormal[];

out vec3 gAmb;
out vec3 gDiff;
out vec3 gSpec;
out vec3 gPosition;
out vec3 gNormal;
out float gShiny;

out vec3 triHeights;

float calcHeight( vec3 p0, vec3 p1, vec3 p2 ) {
    
    //vec3 two = vec3( 2.0, 2.0, 2.0 );

    float a = length( p1 - p2 );
    float b = length( p2 - p0 );
    float c = length( p1 - p0 );
    float beta = acos( ( a*a + c*c - b*b ) / ( 2.0*a*c ) );
    return abs( c * sin( beta ) );
}

void main() {
    
    for( int i = 0; i < 3; i++ ) {
        gl_Position = gl_in[i].gl_Position;
        gAmb = vAmb[i];
        gDiff = vDiff[i];
        gSpec = vSpec[i];
        gShiny = vShiny[i];
        gPosition = vPosition[i];
        gNormal = normalize ( cross( vPosition[1] - vPosition[0], vPosition[2] - vPosition[0] ) );
        /*
        // Ya, they're ternary operators
        // What am I doing with my life
        triHeights = vec3( 
            (i==0) ? 1.0 : 0.0,
            (i==1) ? 1.0 : 0.0,
            (i==2) ? 1.0 : 0.0
        );*/
        
        float height = calcHeight( vPosition[i%3], vPosition[(i+1)%3], vPosition[(i+2)%3] );
        
        // Ya, they're ternary operators
        // What am I doing with my life
        triHeights = vec3(
            (i==0) ? height : 0.0,
            (i==1) ? height : 0.0, 
            (i==2) ? height : 0.0
        );
        
        EmitVertex();
    }

    EndPrimitive();
}