#version 330

in vec2 textureCoordinates;
in vec3 normals;
in vec3 toCameraVector;

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
uniform	float shineDamper;
uniform	float reflectivity;

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

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base,-directionalLight.direction,normal);
}

void main()
{
	outColor = texture2D(sampler, textureCoordinates.xy) * calcDirectionalLight(directionalLight, normalize(normals));
}