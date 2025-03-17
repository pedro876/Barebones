
uniform vec3 _AmbientLight = vec3(0.1);

vec3 GetLighting(vec3 positionWS, vec3 normalWS)
{
	vec3 totalLight = _AmbientLight;

	vec3 lightPos = vec3(0.0, 2.0, 1.0);
	float lightRangeSqr = pow2(4.0);
	float lightIntensity = 2.0;

	vec3 lightDir = lightPos - positionWS;
	float distSqr = dot(lightDir, lightDir);
	lightDir = normalize(lightDir);
	float atten = distSqr / lightRangeSqr;
	atten = 1.0 - saturate(atten);
	atten *= saturate(dot(lightDir, normalWS));
	atten *= lightIntensity;

	totalLight += vec3(atten);

	return totalLight;
}