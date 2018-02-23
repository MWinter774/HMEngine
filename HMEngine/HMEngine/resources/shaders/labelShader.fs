#version 330

in vec2 textureCoordinates;

uniform sampler2D fontAtlas;
uniform vec3 textColor;

out vec4 outColor;

void main(void)
{
	outColor = vec4(textColor, texture2D(fontAtlas, textureCoordinates).a);
}