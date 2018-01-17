#version 330

in vec2 textureCoordinates;
in vec3 normals;
in vec3 worldPosition;
in vec3 toCameraVector;

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
uniform PointLight pointLight;
uniform	float shineDamper;
uniform	float reflectivity;

vec4 calcLight (BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0,0,0,0);
	
	vec4 specularColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
	
        vec3 reflectDirection = normalize(reflect(direction, normal));
		
        float specularFactor = dot(toCameraVector, reflectDirection);
        specularFactor = pow(reflectivity, shineDamper);
        
        if(specularFactor > 0)
        {
            specularColor = vec4(base.color, 1.0) * reflectivity * shineDamper;
        } 
	}
    
    return diffuseColor + specularColor;
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

	return color / attenuation;
}

void main()
{
	outColor = texture2D(sampler, textureCoordinates.xy) * calcPointLight(pointLight, normalize(normals));
}