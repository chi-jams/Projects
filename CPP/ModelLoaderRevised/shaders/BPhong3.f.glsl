#version 410 core

in vec3 gAmb;
in vec3 gDiff;
in vec3 gSpec;
in vec3 gPosition;
in vec3 gNormal;
in float gShiny;

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

void main()
{
    vec3 lightDir = normalize( lightPos - gPosition );
    vec3 n = normalize( gNormal );

    vec3 diffuse = lightD * gDiff * max( dot( lightDir, gNormal ), 0.0 );

    vec3 halfway = normalize( lightDir + viewVector );
    vec3 specular = lightS * gSpec * pow( max( dot( halfway, n ), 0.0 ), gShiny );

    vec3 ambient = gAmb * lightA;

    fColor = vec4( ambient + diffuse + specular, 1.0 ); 

} 