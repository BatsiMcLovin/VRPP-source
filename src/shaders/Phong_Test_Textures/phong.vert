#version 330

layout (location = 0) in vec4 positionAttribute;
layout (location = 1) in vec2 uvCoordAttribute;
layout (location = 2) in vec4 normalAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformInverse;
uniform mat4 uniformPerspective;

out vec3 passNormal;
out vec3 passLightPosition;
out vec3 passPosition;
out vec2 passUVCoords;

void main() {
    passLightPosition = (uniformView * vec4(3,3,3,1)).xyz;

    gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;

    //transform the position correctly into view space
    //and pass it to the fragment shader
    passPosition = (uniformView * uniformModel * positionAttribute).xyz;

    //transform the normal correctly into view space 
    //and pass it to the fragment shader
    passNormal = normalize((uniformInverse * normalAttribute).xyz);
	
	passUVCoords = uvCoordAttribute;
}