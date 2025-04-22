#version 330 core

#include "Core/Assets/ShaderLibrary/Common.glsl"
#include "Core/Assets/ShaderLibrary/Lighting.glsl"

#MaterialProperties
uniform sampler2D _BaseMap = texture(white);
uniform sampler2D _EmissiveMap = texture(black);
uniform vec3 _BaseColor = vec3(1,1,1);

#Attributes
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

#Varyings
vec3 vertexColor;
vec2 texCoord;
vec3 positionWS;
vec3 normalWS;

#Outputs
out vec4 FragColor;

#Vertex
void main()
{
	vertexColor = aNormal * 0.5 + 0.5;
    texCoord = aTexCoord;
    positionWS = (_Model * vec4(aPos, 1.0)).xyz;
    normalWS = (_Model * vec4(aNormal, 0.0)).xyz;
    gl_Position = _ViewProj * vec4(positionWS, 1.0);
}

#Fragment
void main()
{
    vec4 base = texture(_BaseMap, texCoord);
    vec4 emissive = texture(_EmissiveMap, texCoord);
    base.rgb *= _BaseColor;
	base.rgb *= GetLighting(positionWS, normalWS);
    base.rgb += emissive.rgb;
    vec3 outColor = base.rgb;
    //vec3 outColor = normalWS * 0.5 + 0.5;
    FragColor = vec4(outColor, 1.0);
}