#version 410 core

in vec3 gAmb;
in vec3 gDiff;
in vec3 gSpec;
in vec3 gPosition;
in vec3 gNormal;
in float gShiny;

in vec3 triHeights;

out vec4 fColor;

//uniform vec3 viewVector;

uniform bool useWireframe;

layout (std140) uniform Matrices {
    mat4 view;
    mat4 projection;
    vec3 viewVector;
};

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
    vec3 lightDir = normalize( lightPos.xyz - gPosition );
    vec3 n = normalize( gNormal );

    vec3 diffuse = lightD.xyz * gDiff * max( dot( lightDir, gNormal ), 0.0 );

    vec3 halfway = normalize( lightDir + viewVector );
    vec3 specular = lightS.xyz * gSpec * pow( max( dot( halfway, n ), 0.0 ), gShiny );

    vec3 ambient = gAmb.xyz * lightA.xyz;

    vec4 edgeColor = vec4( 0.7, 0.7, 0.7, 1.0 );

    float minDistance = min( triHeights.x, triHeights.y );
          minDistance = min( minDistance, triHeights.z );

    float edgeWidth = 0.02;

    if( useWireframe ){
        float mixVal = smoothstep( 0.0, edgeWidth, minDistance );
        vec4 outColor = vec4( ambient + diffuse + specular, 1.0 );
        fColor = mix( edgeColor, outColor, mixVal );
    }
    else {
        fColor = vec4( ambient + diffuse + specular, 1.0 );
    }

} 