#version 330 core

#GlobalProperties
uniform mat4 _ModelViewProj;

#MaterialProperties
uniform sampler2D _BaseMap;
uniform vec3 _BaseColor = vec3(1,1,1);

#Varyings
vec3 vertexColor;
vec2 texCoord;

#Vertex

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

void main()
{
	vertexColor = aNormal * 0.5 + 0.5;
    texCoord = aTexCoord;
    gl_Position = _ModelViewProj * vec4(aPos, 1.0);
}

#Fragment

out vec4 FragColor;

void main()
{
	vec3 outColor = texture(_BaseMap, texCoord).rgb * _BaseColor;
    FragColor = vec4(outColor, 1.0);
    //FragColor = vec4(texCoord, 0.0, 1.0);
}