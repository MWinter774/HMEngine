#version 330

in vec2 textureCoordinates;

uniform sampler2D sampler;
uniform vec3 ambientLight;

in vec3 pos;

out vec4 outColor;

void main()
{
	//gl_fragColor = vec4(1.0,0.0,0.0,1.0);
	vec4 textureColor = texture2D(sampler, textureCoordinates.xy);
	if(textureColor.a<0.5)
	{
		discard;
	}
	
	outColor = textureColor * vec4(ambientLight, 1.0f);
}