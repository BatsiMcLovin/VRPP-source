#version 330

layout (location = 0) in vec4 positionAttr;
layout (location = 1) in vec2 uvCoordAttr;
layout (location = 2) in vec4 normalAttr;

uniform mat4 uniModelMat;
uniform mat4 uniViewMat;
uniform mat4 uniInverse;
uniform mat4 uniPerspMat;

out vec3 positionPass;
out vec3 normalPass;
out vec2 uvCoordPass;
out vec3 worldPass;

void main() {

gl_Position = uniPerspMat*uniViewMat*uniModelMat*positionAttr;

uvCoordPass = uvCoordAttr;

positionPass = (uniViewMat*uniModelMat*positionAttr).xyz;

normalPass = normalize((uniInverse*normalAttr).xyz);
}