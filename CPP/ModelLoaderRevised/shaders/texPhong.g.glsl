
#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vPosition[];
in vec3 vNormal[];
in vec2 vTexCoord[];

out vec3 gPosition;
out vec3 gNormal;
out vec2 gTexCoord;

void main() {
    
    for( int i = 0; i < 3; i++ ) {
        gl_Position = gl_in[i].gl_Position;
        gTexCoord = vTexCoord[i];
        gPosition = vPosition[i];
        gNormal = normalize ( cross( vPosition[1] - vPosition[0], vPosition[2] - vPosition[0] ) );
        EmitVertex();
    }

    EndPrimitive();
}