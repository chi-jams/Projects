#version 410 core

layout (std140) uniform Matrices {
    mat4 view;
    mat4 projection;
    vec3 viewVector;
};

layout( location = 0 ) in vec4 vertex;
layout( location = 1 ) in vec4 normal;

layout( location = 2 ) in vec2 texCoord;

layout( location = 6 ) in mat4 model;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
    gl_Position = projection * view * model * vertex;

    // Everything's already in a position where we can
    // do the lighting calculations, so that's why
    // the normal/vertex aren't multiplied by any matrices
    // Normally we would, but tl;dr it's precalculated
    vNormal = normal.xyz;
    vPosition = vertex.xyz;

    vTexCoord = texCoord;

}