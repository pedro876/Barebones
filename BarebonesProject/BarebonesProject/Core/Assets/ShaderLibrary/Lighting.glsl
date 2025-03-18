
//uniform vec3 _AmbientLight = vec3(0.1);

layout (std140) uniform Lights
{
	vec3 _AmbientLight;
};

struct Light
{
	vec3 positionWS;
	float invSqrRange;
	float intensity;
};

float DistanceAttenuation(Light light, float distanceSqr, vec3 positionWS)
{
	return Square(saturate(1.0 - Square(distanceSqr * light.invSqrRange)));
}

vec3 GetLighting(vec3 positionWS, vec3 normalWS)
{
	vec3 totalLight = _AmbientLight;

	Light light;
	light.positionWS = vec3(0.0, 2.0, 1.0);
	light.intensity = 2.0;
	light.invSqrRange = 1.0 / Square(4.0);

	vec3 lightDir = light.positionWS - positionWS;
	float distSqr = dot(lightDir, lightDir);
	lightDir = normalize(lightDir);

	float atten = DistanceAttenuation(light, distSqr, positionWS);
	atten *= saturate(dot(lightDir, normalWS));
	atten *= light.intensity;

	totalLight += vec3(atten);

	return totalLight;
}