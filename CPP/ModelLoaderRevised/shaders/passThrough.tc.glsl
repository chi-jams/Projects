#version 410 core

layout(vertices=1) out;

uniform float tessLevel;

in vec3 vAmb[];
in vec3 vDiff[];
in vec3 vSpec[];
in float vShiny[];
in vec3 vPosition[];
in vec3 vNormal[];

patch out vec3  tcAmb;
patch out vec3  tcDiff;
patch out vec3  tcSpec;
patch out float tcShiny;
out vec3  tcPosition[];
out vec3  tcNormal[];

void main() {
    // Pass along vertex position unmodified
    gl_out[ gl_InvocationID ].gl_Position = gl_in[ gl_InvocationID ].gl_Position;

    tcAmb = vAmb[ gl_InvocationID ];
    tcDiff = vDiff[ gl_InvocationID ];
    tcSpec = vSpec[ gl_InvocationID ];
    tcShiny = vShiny[ gl_InvocationID ];
    tcPosition[ gl_InvocationID ] = vPosition[ gl_InvocationID ];
    tcNormal[ gl_InvocationID ] = vNormal[ gl_InvocationID ];

    // Specify Outer and Inner Tessellation Levels
    for( int i = 0; i < 4; i++ ) {
        gl_TessLevelOuter[i] = tessLevel;
    }
    for( int i = 0; i < 2; i++ ) {  
        gl_TessLevelInner[i] = tessLevel;
    }

}