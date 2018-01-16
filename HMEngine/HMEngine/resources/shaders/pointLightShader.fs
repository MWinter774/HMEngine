#version 450

in vec2 textureCoordinates0;
in vec3 surfaceNormal;
in vec3 worldPosition0;
in vec3 toCameraVector;

out vec4 outColor;

struct Material
{
	vec3 materialColor;
	float shineDamper;
	float reflectivity;
};

struct BaseLight
{
	vec3 lightColor;
	float intensity;
};

struct PointLight
{
	BaseLight baseLight;
	vec3 attenuation;
	vec3 position;
	float range;
};

uniform sampler2D sampler;
uniform PointLight pointLight;
uniform Material material;

vec4 CalculateLight(BaseLight baseLight, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
    
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    if(diffuseFactor > 0)
    {
        diffuseColor = vec4(baseLight.lightColor, 1.0) * baseLight.intensity * diffuseFactor;
        
        vec3 reflectDirection = normalize(reflect(direction, normal));
		
        float specularFactor = dot(toCameraVector, reflectDirection);
        specularFactor = pow(material.reflectivity, material.shineDamper);
        
        if(specularFactor > 0)
        {
            specularColor = vec4(baseLight.lightColor, 1.0) * material.reflectivity * material.shineDamper;
        } 
	}
    
    return diffuseColor + specularColor;
}

vec4 CalculatePointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = worldPosition0 - pointLight.position;
	float distanceToPointLight = length(lightDirection);
	
	if(distanceToPointLight > pointLight.range)
		return vec4(0, 0, 0, 0);
	
	lightDirection = normalize(lightDirection);
	
	vec4 color = CalculateLight(pointLight.baseLight, lightDirection, normal);
	
	float attenuation = pointLight.attenuation.x + pointLight.attenuation.y * distanceToPointLight + pointLight.attenuation.z * distanceToPointLight * distanceToPointLight + 0.0001; 

	return color / attenuation;
}

void main()
{
	vec4 needButUseless = (vec4(material.materialColor, 1) / vec4(material.materialColor, 1));
	outColor = texture2D(sampler, textureCoordinates0.xy) * CalculatePointLight(pointLight, normalize(surfaceNormal)) * needButUseless;
}