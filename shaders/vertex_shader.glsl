#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 vFragPos;
out vec3 vNormal;
out vec2 vTexCoords;
out vec4 vFragPosLightSpace;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightSpaceMatrix;

void main()
{
    vFragPos = vec3(uModel * vec4(aPosition, 1.0));
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vTexCoords = aTexCoords;
    vFragPosLightSpace = uLightSpaceMatrix * vec4(vFragPos, 1.0);
    gl_Position = uProjection * uView * vec4(vFragPos, 1.0);
}