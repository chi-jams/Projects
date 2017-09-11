
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

void main() {
    
    for( int i = 0; i < 3; i++ ) {
        gl_Position = gl_in[i].gl_Position;
        gAmb = vAmb[i];
        gDiff = vDiff[i];
        gSpec = vSpec[i];
        gShiny = vShiny[i];
        gPosition = vPosition[i];
        gNormal = normalize ( cross( vPosition[1] - vPosition[0], vPosition[2] - vPosition[0] ) );
        EmitVertex();
    }

    EndPrimitive();
}