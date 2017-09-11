#version 410 core

in vec3 vAmb;
in vec3 vDiff;
in vec3 vSpec;
in float vShiny;
in vec3 vPosition;
in vec3 vNormal;

out vec4 fColor;

// Make a point light
layout (std140) uniform Light {
    vec4 lightPos;
    vec4 lightA;
    vec4 lightD;
    vec4 lightS;
    float lightShininess;
};

void main()
{
    
    fColor = vec4( 0, 1, 0, 1 );
} 