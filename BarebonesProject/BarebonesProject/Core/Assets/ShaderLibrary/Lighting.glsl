#Fragment

#define MAX_LIGHT_COUNT 64

layout (std140) uniform Lights
{																						// base alignment	// aligned offset
	vec4 _AmbientLight;																	// 16				// 0
	vec4 _DirectionalLightColor;														// 16				// 16
	vec4 _DirectionalLightDir;															// 16				// 32
	uint _LightCount;																	// 4				// 48
	vec4 _LightPositions[MAX_LIGHT_COUNT];	//xyz = positionWS, w = invSqrRange			// 16				// 64
	vec4 _LightColors[MAX_LIGHT_COUNT];		//xyz = color								// 16				// 1088
	vec4 _LightDirections[MAX_LIGHT_COUNT];	//xyz = direction							// 16				// 2112
	vec4 _LightProperties[MAX_LIGHT_COUNT];	//x = outerCos, y = invOuterMinusInnerCos	// 16				// 3136
};

struct DirectionalLight
{
	bool exists;
	vec3 directionWS;
	vec3 color;
};

struct Light
{
	vec3 positionWS;
	vec3 directionWS;
	float invSqrRange;
	vec3 color;
	float outerCos;
	float invOuterMinusInnerCos;
};

DirectionalLight GetDirectionalLight()
{
	DirectionalLight light;
	light.exists = _DirectionalLightColor.w > 0.5;
	light.directionWS = _DirectionalLightDir.xyz;
	light.color = _DirectionalLightColor.xyz;
	return light;
}

Light GetLight(uint index)
{
	Light light;
	light.positionWS = _LightPositions[index].xyz;
	light.invSqrRange = _LightPositions[index].w;
	light.color = _LightColors[index].xyz;
	light.directionWS = _LightDirections[index].xyz;
	light.outerCos = _LightProperties[index].x;
	light.invOuterMinusInnerCos = _LightProperties[index].y;
	return light;
}

float AngleAttenuation(vec3 lightDir, vec3 normalWS)
{
	float atten = saturate(dot(lightDir, normalWS));
	return atten;
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

vec3 GetLighting(vec3 positionWS, vec3 normalWS)
{
	vec3 totalLight = _AmbientLight.xyz;

	DirectionalLight sun = GetDirectionalLight();
	if(sun.exists)
	{
		totalLight += sun.color * AngleAttenuation(-sun.directionWS, normalWS);
	}

	for(uint i = 0u; i < _LightCount; i++)
	{
		Light light = GetLight(i);

		vec3 lightDir = light.positionWS - positionWS;
		float distSqr = dot(lightDir, lightDir);
		lightDir = normalize(lightDir);

		float atten = DistanceAttenuation(light, distSqr, positionWS);
		atten *= AngleAttenuation(lightDir, normalWS);
		atten *= SpotAttenuation(light, lightDir);

		totalLight += light.color * atten;
	}

	//Light l = GetLight(1u);
	//return vec3(l.innerCos > 0.77 && l.innerCos < 0.79 ? 1.0 : 0.0);

	return totalLight;
}