#version 460

in vec2 textureCoordinates;

uniform sampler2D sampler;
uniform vec3 ambientLight;

out vec4 outColor;

void main()
{
	outColor = texture2D(sampler, textureCoordinates.xy) * vec4(ambientLight, 1.0);
}