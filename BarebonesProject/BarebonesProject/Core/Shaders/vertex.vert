#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 _ModelViewProj;

out vec3 vertexColor;

void main()
{
    vertexColor = aNormal * 0.5 + 0.5;
    gl_Position = _ModelViewProj * vec4(aPos, 1.0);
}