#version 330

in vec2 textureCoordinates;
in vec3 normals;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

uniform sampler2D sampler;
uniform DirectionalLight directionalLight;

out vec4 outColor;

//DirectionalLight

//base function to calculate lights
vec4 calcLight (BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0,0,0,0);
	
	vec4 specularColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color,1.0) * base.intensity * diffuseFactor;
	}
	
	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base,-directionalLight.direction,normal);
}

void main()
{
	outColor = texture2D(sampler, textureCoordinates.xy) * calcDirectionalLight(directionalLight, normalize(normals));
}