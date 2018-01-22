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
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;
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
	vec4 blendMapColor = texture2D(blendMap, textureCoordinates / 40);
	float backgroundTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledUV = textureCoordinates;
	
	/* Calculates amount of color from each texture according to the blend map */
	vec4 backgroundTextureColor = texture2D(sampler, tiledUV) * backgroundTextureAmount;
	vec4 rTextureColor = texture2D(rTexture, tiledUV) * blendMapColor.r;
	vec4 gTextureColor = texture2D(gTexture, tiledUV) * blendMapColor.g;
	vec4 bTextureColor = texture2D(bTexture, tiledUV) * blendMapColor.b;
	
	vec4 textureColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;

	outColor = textureColor * calcDirectionalLight(directionalLight, normalize(normals));
}