#version 460

in vec2 textureCoordinates;
in vec3 normals;
in vec3 worldPosition;

out vec4 outColor;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct PointLight
{
	BaseLight base;
	vec3 attenuation;
	vec3 position;
	float range;
};

uniform sampler2D sampler;
uniform vec3 ambientLight;

uniform PointLight pointLight;

vec4 calcLight (BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0,0,0,0);
	
	vec4 specularColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
	}
	
	return diffuseColor;
}

vec4 calcPointLight(PointLight pLight, vec3 normal)
{
	vec3 lightDirection = worldPosition - pLight.position;
	float distanceToPointLight = length(lightDirection);
	
	if(distanceToPointLight > pLight.range)
		return vec4(0, 0, 0, 0);
	
	lightDirection = normalize(lightDirection);
	
	vec4 color = calcLight(pLight.base, lightDirection, normal);
	
	float attenuation = pLight.attenuation.x + pLight.attenuation.y * distanceToPointLight + pLight.attenuation.z * distanceToPointLight * distanceToPointLight + 0.0001; 

	return color * attenuation;
}

void main()
{
/*
	vec4 totalLight = vec4(ambientLight, 1.0f);
	vec3 normal = normalize(normals);
	
	totalLight += calcPointLight(pointLight, normal);
	
	outColor = texture2D(sampler, textureCoordinates.xy) * totalLight;*/
	outColor = texture2D(sampler, textureCoordinates.xy) * calcPointLight(pointLight, normalize(normals));
}