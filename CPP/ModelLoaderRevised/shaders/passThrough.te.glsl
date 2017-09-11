#version 410 core

layout( quads, equal_spacing, ccw ) in;

patch in vec3  tcAmb;
patch in vec3  tcDiff;
patch in vec3  tcSpec;
patch in float tcShiny;
in vec3  tcPosition[];
in vec3  tcNormal[];

out vec3  teAmb;
out vec3  teDiff;
out vec3  teSpec;
out float teShiny;
out vec3  tePosition;
out vec3  teNormal;


void main() {
    float u = gl_TessCoord.x; // get parameters
    float v = gl_TessCoord.y;

    // output point in Clip Space
    gl_Position = gl_in[0].gl_Position;

    teAmb = tcAmb;
    teDiff = tcDiff;
    teSpec = tcSpec;
    teShiny = tcShiny;
    tePosition = tcPosition[0];
    teNormal = tcPosition[0];
} 