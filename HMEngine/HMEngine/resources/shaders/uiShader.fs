#version 330

in vec2 textureCoordinates;

uniform sampler2D sampler;

out vec4 outColor;

void main(void)
{	
	outColor = texture2D(sampler, textureCoordinates);
}