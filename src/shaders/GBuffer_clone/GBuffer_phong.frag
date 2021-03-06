#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;

uniform float shininess;

uniform float diffuseColor;

//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
layout(location = 3) out vec4 materialOutput;
 
void main(){  
    positionOutput = passPosition;
    normalOutput = vec4(normalize(passNormal), 0);
    colorOutput = diffuseColor;
    materialOutput = vec4(shininess, 0.0, 0.0, 0.0);
}
