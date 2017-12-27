#version 450

in vec2 textureCoordinates;

uniform sampler2D sampler;
in vec3 pos;

out vec4 outColor;

void main()
{
	//gl_fragColor = vec4(1.0,0.0,0.0,1.0);
	outColor = texture2D(sampler, textureCoordinates.xy);

}