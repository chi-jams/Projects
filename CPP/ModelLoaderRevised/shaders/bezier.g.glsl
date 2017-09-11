
#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3  teAmb[];
in vec3  teDiff[];
in vec3  teSpec[];
in float teShiny[];
in vec3  tePosition[];
in vec3  teVertex[];
in vec3  teNormal[];

out vec3 gAmb;
out vec3 gDiff;
out vec3 gSpec;
out vec3 gPosition;
out vec3 gVertex;
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
        gAmb = teAmb[i];
        gDiff = teDiff[i];
        gSpec = teSpec[i];
        gShiny = teShiny[i];
        gPosition = tePosition[i];
        gVertex = teVertex[i];
        gNormal = teNormal[i];
        // Don't do this in the geometry shader when we're interpolating;
        // It makes the whole thing have a gourad look to it rather than
        // making everything smooth
        //gNormal = normalize ( cross( tePosition[1] - tePosition[0], tePosition[2] - tePosition[0] ) );
        /*
        // Ya, they're ternary operators
        // What am I doing with my life
        triHeights = vec3( 
            (i==0) ? 1.0 : 0.0,
            (i==1) ? 1.0 : 0.0,
            (i==2) ? 1.0 : 0.0
        );*/
        
        float height = calcHeight( tePosition[i%3], tePosition[(i+1)%3], tePosition[(i+2)%3] );
        
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