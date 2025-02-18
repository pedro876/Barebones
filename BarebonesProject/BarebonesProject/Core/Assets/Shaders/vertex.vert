#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 _ModelViewProj;

out vec3 vertexColor;
out vec2 texCoord;

void main()
{
    vertexColor = aNormal * 0.5 + 0.5;
    texCoord = aTexCoord;
    gl_Position = _ModelViewProj * vec4(aPos, 1.0);
}