//uniform vec3 _AmbientLight = vec3(0.1);

#define MAX_LIGHT_COUNT 64

layout (std140) uniform Lights
{																				// base alignment	// aligned offset
	vec4 _AmbientLight;															// 16				// 0
	uint _LightCount;															// 4				// 16
	vec4 _LightPositions[MAX_LIGHT_COUNT];	//xyz = positionWS, w = invSqrRange	// 16				// 32
	vec4 _LightProperties[MAX_LIGHT_COUNT]; //x = intensity						// 16				// 1056
};

struct Light
{
	vec3 positionWS;
	float invSqrRange;
	float intensity;
};

Light GetLight(uint index)
{
	Light light;
	light.positionWS = _LightPositions[index].xyz;
	light.invSqrRange = _LightPositions[index].w;
	light.intensity = _LightProperties[index].x;
	return light;
}

float DistanceAttenuation(Light light, float distanceSqr, vec3 positionWS)
{
	return Square(saturate(1.0 - Square(distanceSqr * light.invSqrRange)));
}

vec3 GetLighting(vec3 positionWS, vec3 normalWS)
{
	vec3 totalLight = _AmbientLight.xyz;

	//Light light;
	//light.positionWS = vec3(0.0, 2.0, 1.0);
	//light.intensity = 2.0;
	//light.invSqrRange = 1.0 / Square(4.0);

	for(uint i = 0u; i < _LightCount; i++)
	{
		Light light = GetLight(i);

		vec3 lightDir = light.positionWS - positionWS;
		float distSqr = dot(lightDir, lightDir);
		lightDir = normalize(lightDir);

		float atten = DistanceAttenuation(light, distSqr, positionWS);
		atten *= saturate(dot(lightDir, normalWS));
		atten *= light.intensity;

		totalLight += vec3(atten);
	}

	return totalLight;
}