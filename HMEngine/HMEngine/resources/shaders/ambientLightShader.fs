#version 330

in vec2 textureCoordinates;

out vec4 outColor;

uniform sampler2D sampler;
uniform vec3 ambientLight;

void main()
{
	outColor = texture2D(sampler, textureCoordinates.xy) * vec4(ambientLight, 1.0);
}