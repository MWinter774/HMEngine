#version 330

in vec2 textureCoordinates;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform vec3 ambientLight;
uniform vec3 skyColor;

in vec3 pos;
in float visibilty;

out vec4 outColor;

void main()
{
	vec4 blendMapColor = texture2D(blendMap, textureCoordinates);
	float backgroundTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledUV = 40.0 * textureCoordinates;
	
	/* Calculates amount of color from each texture according to the blend map */
	vec4 backgroundTextureColor = texture2D(backgroundTexture, tiledUV) * backgroundTextureAmount;
	vec4 rTextureColor = texture2D(rTexture, tiledUV) * blendMapColor.r;
	vec4 gTextureColor = texture2D(gTexture, tiledUV) * blendMapColor.g;
	vec4 bTextureColor = texture2D(bTexture, tiledUV) * blendMapColor.b;
	
	vec4 textureColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
	if(textureColor.a<0.5)
	{
		discard;
	}
	
	outColor = textureColor * vec4(ambientLight, 1.0f);
	outColor = mix(vec4(skyColor, 1.0), outColor, visibilty);
}