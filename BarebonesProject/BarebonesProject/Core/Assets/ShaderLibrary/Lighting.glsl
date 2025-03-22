//uniform vec3 _AmbientLight = vec3(0.1);

#define MAX_LIGHT_COUNT 64

layout (std140) uniform Lights
{																						// base alignment	// aligned offset
	vec4 _AmbientLight;																	// 16				// 0
	uint _LightCount;																	// 4				// 16
	vec4 _LightPositions[MAX_LIGHT_COUNT];	//xyz = positionWS, w = invSqrRange			// 16				// 32
	vec4 _LightColors[MAX_LIGHT_COUNT];		//xyz = color								// 16				// 1056
	vec4 _LightDirections[MAX_LIGHT_COUNT];	//xyz = direction							// 16				// 2080
	vec4 _LightProperties[MAX_LIGHT_COUNT];	//x = outerCos, y = invOuterMinusInnerCos	// 16				// 3104
};

struct Light
{
	vec3 positionWS;
	vec3 directionWS;
	float invSqrRange;
	vec3 color;
	float outerCos;
	float innerCos;
	float invOuterMinusInnerCos;
};

Light GetLight(uint index)
{
	Light light;
	light.positionWS = _LightPositions[index].xyz;
	light.invSqrRange = _LightPositions[index].w;
	light.color = _LightColors[index].xyz;
	light.directionWS = _LightDirections[index].xyz;
	light.outerCos = _LightProperties[index].z;
	light.innerCos = _LightProperties[index].w;
	light.invOuterMinusInnerCos = _LightProperties[index].y;
	return light;
}

float DistanceAttenuation(Light light, float distanceSqr, vec3 positionWS)
{
	float atten = Square(saturate(1.0 - Square(distanceSqr * light.invSqrRange)));
	return atten;
}

float SpotAttenuation(Light light, vec3 lightDir)
{
	float angle = saturate(dot(-lightDir, light.directionWS));
	float atten = Square(saturate((angle - light.outerCos) * light.invOuterMinusInnerCos));
	return atten;
}

float AngleAttenuation(Light light, vec3 lightDir, vec3 normalWS)
{
	float atten = saturate(dot(lightDir, normalWS));
	return atten;
}

vec3 GetLighting(vec3 positionWS, vec3 normalWS)
{
	vec3 totalLight = _AmbientLight.xyz;

	for(uint i = 0u; i < _LightCount; i++)
	{
		Light light = GetLight(i);

		vec3 lightDir = light.positionWS - positionWS;
		float distSqr = dot(lightDir, lightDir);
		lightDir = normalize(lightDir);

		float atten = DistanceAttenuation(light, distSqr, positionWS);
		atten *= AngleAttenuation(light, lightDir, normalWS);
		atten *= SpotAttenuation(light, lightDir);

		totalLight += light.color * atten;
	}

	//Light l = GetLight(1u);
	//return vec3(l.innerCos > 0.77 && l.innerCos < 0.79 ? 1.0 : 0.0);

	return totalLight;
}