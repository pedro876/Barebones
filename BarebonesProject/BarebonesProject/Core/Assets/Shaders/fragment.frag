#version 330 core

in vec3 vertexColor;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D _BaseMap;

void main()
{
    vec3 outColor = texture(_BaseMap, texCoord).rgb;
    FragColor = vec4(outColor, 1.0);
    //FragColor = vec4(texCoord, 0.0, 1.0);
}