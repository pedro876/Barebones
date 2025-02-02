#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 _ModelViewProj;

void main()
{
    gl_Position = _ModelViewProj * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);
}